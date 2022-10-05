/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:34:27 by schuah            #+#    #+#             */
/*   Updated: 2022/10/05 19:13:00 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Connects the current node of the argument with the list of files
 * 
 * @param current The current node of the argument
 * @param files The list of files
 * @param output The content that suppposingly will house the current node
 * @return t_list* Next node of the argument (Excluding the files)
 */
t_list	*connect_cur_with_cur(t_list *current, t_list *files, char *output)
{
	t_list	*end;

	end = current->next;
	ft_lstlast(files)->next = current->next;
	free(current->content);
	current->content = files->content;
	current->next = files->next;
	free(output);
	free(files);
	return (end);
}

/**
 * @brief Checks the final output and whether there was a conversion for $. If
 * final output is NULL, replaces it 
 * 
 * @param current The current node of the argument
 * @param output The content that will house the current node's content
 * @param dollar Whether a dollar conversion had taken place
 * @return t_list* next node of the argument
 */
t_list	*check_output_dollar(t_list *current, char *output, int dollar)
{
	if (output == NULL)
	{
		free(current->content);
		current->content = ft_calloc(1, sizeof(char *));
		*(char **)current->content = NULL;
	}
	else if (dollar == 0)
		*(char **)current->content = output;
	return (current->next);
}

/**
 * @brief Checks and expands the mandatory characters: '', "" and $, calling
 * their respective functions to do its respective expansion. If non of these
 * special characters are found, append the character to the output instead
 * 
 * @param main The main struct containing the environment list
 * @param cur_in The current node of the argument linked list
 * @param exp The expansion struct containing the argument, i position and
 * output string
 * @return int 1 if expansion of $ is done, else 0
 */
int	expand_mandatory(t_main *main, t_list **cur_in, t_expand *exp)
{
	t_list	*current;
	int		dollar;

	dollar = 0;
	current = *cur_in;
	if (*(exp->arg + exp->i) == '\'')
		expand_squote(exp);
	else if (*(exp->arg + exp->i) == '\"')
		expand_dquote(main, exp);
	else if (*(exp->arg + exp->i) == '$')
	{
		dollar = expand_dlr(&current, exp, dlr_val(main, exp->arg + exp->i));
		while (exp->arg[exp->i + 1] != '\0' && exp->arg[exp->i + 1] != '\''
			&& exp->arg[exp->i + 1] != '\"' && exp->arg[exp->i + 1] != '$')
				exp->i++;
	}
	else
		exp->output = append_char(exp->output, *(exp->arg + exp->i));
	exp->i++;
	*cur_in = current;
	return (dollar);
}

void	recurs_expand_dollar(t_main *main, t_expand *exp)
{
	char	*dollar_expanded;
	int		i;

	if (*(exp->arg + exp->i + 1) != '$')
		return ;
	exp->i++;
	i = -1;
	dollar_expanded = dlr_val(main, exp->arg + exp->i);
	if (dollar_expanded != NULL)
		while (dollar_expanded[++i] != '\0' && dollar_expanded[0] != '\0')
			exp->output = append_char(exp->output, dollar_expanded[i]);
	while (exp->arg[exp->i + 1] != '\0' && exp->arg[exp->i + 1] != '\''
		&& exp->arg[exp->i + 1] != '\"' && exp->arg[exp->i + 1] != '$')
			exp->i++;
	free(dollar_expanded);
	recurs_expand_dollar(main, exp);
}

t_list	*expand(t_main *main, t_expand *exp, t_list *current)
{
	int		quote;
	int		dollar;

	quote = 0;
	exp->i = 0;
	exp->output = NULL;
	while (*(exp->arg + exp->i) != '\0')
	{
		dollar = 0;
		if (*(exp->arg + exp->i) == '\'')
		{
			if (ft_strchr(exp->arg, '*') != NULL)
				exp->output = append_char(exp->output, '\'');
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
		}
		else if (*(exp->arg + exp->i) == '$' && quote == 0)
		{
			dollar = expand_dlr(&current, exp, dlr_val(main, exp->arg + exp->i));
			while (exp->arg[exp->i + 1] != '\0' && exp->arg[exp->i + 1] != '\''
				&& exp->arg[exp->i + 1] != '\"' && exp->arg[exp->i + 1] != '$'
				&& exp->arg[exp->i + 1] != '*')
					exp->i++;
		}
		else if (*(exp->arg + exp->i) == '\"' && quote == 0)
		{
			if (*(exp->arg + exp->i + 1) == '$')
				recurs_expand_dollar(main, exp);
			if (*(exp->arg + exp->i + 1) == '*')
			{
				exp->output = append_char(exp->output, '\'');
				while (*(exp->arg + ++exp->i) != '\0' && *(exp->arg + exp->i) != '\"')
					exp->output = append_char(exp->output, *(exp->arg + exp->i));
				exp->output = append_char(exp->output, '\'');
				break ;
			}
		}
		else
			exp->output = append_char(exp->output, *(exp->arg + exp->i));
		exp->i++;
	}
	return (check_output_dollar(current, exp->output, dollar));
}

t_list	*expand2(t_expand *exp, t_list *current)
{
	t_list	*files;
	int		dollar;
	int		quote;

	quote = 0;
	exp->i = 0;
	exp->output = ft_calloc(1, sizeof(char *));
	dollar = 0;
	if (exp->arg != NULL)
	{
		while (*(exp->arg + exp->i) != '\0' && exp->arg != NULL)
		{
			dollar = 0;
			if (*(exp->arg + exp->i) == '\'')
			{
				if (quote == 0)
					quote = 1;
				else
					quote = 0;
			}
			if (*(exp->arg + exp->i) == '*' && check_star(exp->arg) && quote == 0)
			{
				files = get_files_from_dir(exp->arg);
				if (files == NULL)
				{
					ft_lstclear(&files, &free);
					exp->output = append_char(exp->output, *(exp->arg + exp->i));
				}
				else
					return (connect_cur_with_cur(current, files, exp->output));
			}
			else if (*(exp->arg + exp->i) != '\'')
				exp->output = append_char(exp->output, *(exp->arg + exp->i));
			exp->i++;
		}
	}
	return (check_output_dollar(current, exp->output, dollar));
}

void	expander(t_main *main, t_list **args)
{
	t_list		*arg_lst;
	t_expand	exp;

	arg_lst = *args;
	if (arg_lst == NULL)
	{
		*args = ft_lstnew(ft_calloc(1, sizeof(char *)));
		return ;
	}
	while (arg_lst != NULL)
	{
		exp.arg = *(char **)arg_lst->content;
		arg_lst = expand(main, &exp, arg_lst);
	}
	arg_lst = *args;
	while (arg_lst != NULL)
	{
		exp.arg = *(char **)arg_lst->content;
		arg_lst = expand2(&exp, arg_lst);
		free(exp.arg);
	}
	ft_lstadd_back(args, ft_lstnew(ft_calloc(1, sizeof(char *))));
}
