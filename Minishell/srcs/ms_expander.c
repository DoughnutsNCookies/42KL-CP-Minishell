/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:34:27 by schuah            #+#    #+#             */
/*   Updated: 2022/10/07 12:08:29 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Connects the current node of the argument with the list of files and
 * returns the next node of the argument to be expanded
 * 
 * @param current The current node of the argument
 * @param files The list of files
 * @param output The content that suppposingly will house the current node
 * @return t_list* Next node of the argument to be expanded (Excluding the files)
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
 * final output is NULL, replaces the current node's content with '\0' instead.
 * Else if the final output is not NULL and there is no dollar conversion,
 * replace the current node's content with output.
 * 
 * @param current The current node of the argument
 * @param output The content that will house the current node's content
 * @param dollar Whether a dollar conversion had taken place
 * @return t_list* The next node of the argument linked list to be expanded
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

t_list	*expand_first_phase(t_main *main, t_expand *exp, t_list *current)
{
	int		quote;
	int		dollar;

	quote = 0;
	exp->i = 0;
	exp->output = NULL;
	while (exp->arg[exp->i] != '\0')
	{
		dollar = 0;
		if (exp->arg[exp->i] == '\'')
		{
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
		}
		else if (exp->arg[exp->i] == '$' && quote == 0)
		{
			dollar = expand_dlr(&current, exp, dlr_val(main, &exp->arg[exp->i]));
			while (exp->arg[exp->i + 1] != '\0' && exp->arg[exp->i + 1] != '\''
				&& exp->arg[exp->i + 1] != '\"' && exp->arg[exp->i + 1] != '$'
				&& exp->arg[exp->i + 1] != '*')
					exp->i++;
		}
		else if (exp->arg[exp->i] == '\"' && quote == 0)
		{
			exp->i++;
			while (exp->arg[exp->i] != '\"')
			{
				if (exp->arg[exp->i] == '\'')
				{
					exp->output = append_char(exp->output, '\\');
					exp->output = append_char(exp->output, '\"');
				}
				else if (exp->arg[exp->i] == '$')
				{
					if (exp->arg[exp->i + 1] == '\"' || exp->arg[exp->i + 1] == '\'')
						exp->output = append_char(exp->output, '$');
					else
					{
						exp->i--;
						recurs_expand_dollar(main, exp);
					}
				}
				else if (exp->arg[exp->i] == '*')
				{
					exp->output = append_char(exp->output, '\'');
					exp->i--;
					while (exp->arg[++exp->i] != '\0' && exp->arg[exp->i] != '\"')
						exp->output = append_char(exp->output, exp->arg[exp->i]);
					exp->output = append_char(exp->output, '\'');
					break ;
				}
				else
					exp->output = append_char(exp->output, exp->arg[exp->i]);
				exp->i++;
			}
		}
		else if (exp->arg[exp->i] == '*' && quote == 1)
		{
			exp->output = append_char(exp->output, '\'');
			exp->output = append_char(exp->output, exp->arg[exp->i]);
			exp->output = append_char(exp->output, '\'');
		}
		else
			exp->output = append_char(exp->output, exp->arg[exp->i]);
		exp->i++;
	}
	return (check_output_dollar(current, exp->output, dollar));
}

t_list	*expand_second_phase(t_expand *exp, t_list *current)
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
		while (exp->arg[exp->i] != '\0' && exp->arg != NULL)
		{
			dollar = 0;
			if (exp->arg[exp->i] == '\'')
			{
				if (quote == 0)
					quote = 1;
				else
					quote = 0;
			}
			if (exp->arg[exp->i] == '*' && check_star(exp->arg) && quote == 0)
			{
				files = get_files_from_dir(exp->arg);
				if (files == NULL)
				{
					ft_lstclear(&files, &free);
					while (exp->arg[exp->i + 1] != '\0' && exp->arg[exp->i + 1] != '\''
						&& exp->arg[exp->i + 1] != '\"')
					{
						exp->output = append_char(exp->output, exp->arg[exp->i]);
						exp->i++;
					}
				}
				else
					return (connect_cur_with_cur(current, files, exp->output));
			}
			if (exp->arg[exp->i] == '\\' && exp->arg[exp->i + 1] == '\"')
			{
				exp->output = append_char(exp->output, '\'');
				exp->i++;
			}
			else if (exp->arg[exp->i] != '\'')
				exp->output = append_char(exp->output, exp->arg[exp->i]);
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
		arg_lst = expand_first_phase(main, &exp, arg_lst);
	}
	arg_lst = *args;
	while (arg_lst != NULL)
	{
		exp.arg = *(char **)arg_lst->content;
		arg_lst = expand_second_phase(&exp, arg_lst);
		free(exp.arg);
	}
	ft_lstadd_back(args, ft_lstnew(ft_calloc(1, sizeof(char *))));
}
