/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_debugger.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:38:51 by schuah            #+#    #+#             */
/*   Updated: 2022/10/05 21:02:42 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief To print the linked list
 * 
 * @param head The head of the linked list
 */
void	print_ll(t_list *head)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = head;
	ft_printf("\nPRINTING LL\n");
	while (temp != NULL)
	{
		ft_printf("%d: |%s|\n", i++, *(char **)temp->content);
		temp = temp->next;
	}
	ft_printf("PRINTING END\n");
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
// int	expand_mandatory(t_main *main, t_list **cur_in, t_expand *exp)
// {
// 	t_list	*current;
// 	int		dollar;

// 	dollar = 0;
// 	current = *cur_in;
// 	if (exp->arg[exp->i] == '\'')
// 		expand_squote(exp);
// 	else if (exp->arg[exp->i] == '\"')
// 		expand_dquote(main, exp);
// 	else if (exp->arg[exp->i] == '$')
// 	{
// 		dollar = expand_dlr(&current, exp, dlr_val(main, exp->arg + exp->i));
// 		while (exp->arg[exp->i + 1] != '\0' && exp->arg[exp->i + 1] != '\''
// 			&& exp->arg[exp->i + 1] != '\"' && exp->arg[exp->i + 1] != '$')
// 				exp->i++;
// 	}
// 	else
// 		exp->output = append_char(exp->output, exp->arg[exp->i]);
// 	exp->i++;
// 	*cur_in = current;
// 	return (dollar);
// }

/**
 * @brief Replace the contents of the current node with the list of files and,
 * creates new nodes for every other files
 * 
 * @param cur_in The current node of the argument linked list
 * @param split The singular argument that was split by its respective $ value
 */
// void	replace_cur_with_files(t_list **cur_in, char *split)
// {
// 	t_list	*files;
// 	t_list	*head;
// 	t_list	*current;

// 	current = *cur_in;
// 	files = get_files_from_dir(split);
// 	head = files;
// 	if (files == NULL)
// 		ft_memcpy(current->content, split, sizeof(char *));
// 	else
// 	{
// 		while (files != NULL)
// 		{
// 			ft_memcpy(current->content, files->content, sizeof(char *));
// 			if (files->next != NULL)
// 			{
// 				current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
// 				current = current->next;
// 			}
// 			files = files->next;
// 		}
// 		ft_lstclear(&head, &free);
// 		free(split);
// 	}
// 	*cur_in = current;
// }

/**
 * @brief Expands single quotes, treats all strings inbetween '' as raw strings
 * 
 * @param arg The argument containing the starting ''
 * @param i The current pos of the argument
 * @param output The output that will house the current node's content
 */
// void	expand_squote(t_expand *exp)
// {
// 	while (exp->arg[++exp->i] != '\'' && exp->arg[exp->i] != '\0')
// 		exp->output = append_char(exp->output, exp->arg[exp->i]);
// }

/**
 * @brief Expands double quotes, treats all strings inbetween "" as raw strings
 * except for $, which will be expanded to its respective
 * values
 * 
 * @param main The main struct containing the environment list
 * @param arg The argument contatining the starting ""
 * @param i The current pos of the arguemnt
 * @param output The output that will house the current node's content
 */
// void	expand_dquote(t_main *main, t_expand *exp)
// {
// 	char	*dollar_expanded;
// 	int		j;

// 	exp->output = append_char(exp->output, '\0');
// 	while (exp->arg[++exp->i] != '\"' && exp->arg[exp->i] != '\0')
// 	{
// 		if (exp->arg[exp->i] == '$')
// 		{
// 			dollar_expanded = dlr_val(main, exp->arg + exp->i);
// 			j = -1;
// 			if (dollar_expanded != NULL)
// 			{
// 				while (dollar_expanded[++j] != '\0')
// 					exp->output = append_char(exp->output, dollar_expanded[j]);
// 			}
// 			while (exp->arg[exp->i + 1] != '\0' && exp->arg[exp->i + 1] != '\''
// 				&& exp->arg[exp->i + 1] != '\"' && exp->arg[exp->i + 1] != '$')
// 				exp->i++;
// 			free(dollar_expanded);
// 		}
// 		else
// 			exp->output = append_char(exp->output, exp->arg[exp->i]);
// 	}
// }
