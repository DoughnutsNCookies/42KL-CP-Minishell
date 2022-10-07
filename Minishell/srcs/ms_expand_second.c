/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_second.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:09:14 by schuah            #+#    #+#             */
/*   Updated: 2022/10/07 17:37:04 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief When the files linked-list is NULL, it will clear the files linked list
 * and append the argument to the output instead until a upcoming character is
 * found, which are '\0', '\'' and '\"'
 * 
 * @param files The list of files
 * @param exp The expansion struct containing the argument, i position and
 * output string
 * @return int 1 if the files is not NULL, else 0
 */
static int	files_is_null(t_list *files, t_expand *exp)
{
	if (files != NULL)
		return (1);
	ft_lstclear(&files, &free);
	while (exp->arg[exp->i + 1] != '\0' && exp->arg[exp->i + 1] != '\''
		&& exp->arg[exp->i + 1] != '\"')
	{
		exp->output = append_char(exp->output, exp->arg[exp->i]);
		exp->i++;
	}
	return (0);
}

/**
 * @brief Filters out certain characters to their actual values. For example,
 * from \"Test\" to 'Test'. This function will also filter out anything that is
 * not ''. For example, from 'Test' to Test
 * 
 * @param exp The expansion struct containing the argument, i position and
 * output string
 */
static void	filter_quote(t_expand *exp)
{
	if (exp->arg[exp->i] == '\\' && exp->arg[exp->i + 1] == '\"')
	{
		exp->output = append_char(exp->output, '\'');
		exp->i++;
	}
	else if (exp->arg[exp->i] != '\'')
		exp->output = append_char(exp->output, exp->arg[exp->i]);
	exp->i++;
}

/**
 * @brief This function will be responsible for expanding *, '' and \" passed
 * from the first round of expansion to their respective values. If a * is found,
 * the argument is checked against all files in the current working directory to
 * find a match, using any valid files to extend the argument linked list.
 * 
 * @param exp The expansion struct containing the argument, i position and
 * output string
 * @param current The current node of the argument linked list
 * @return t_list* Next node of the argument to be expanded (Excluding the files)
 */
t_list	*expand_second_phase(t_expand *exp, t_list *current)
{
	t_list	*files;
	int		dollar;
	int		quote;

	quote = 0;
	exp->i = 0;
	exp->output = ft_calloc(1, sizeof(char *));
	dollar = 0;
	if (exp->arg == NULL)
		return (check_output_dollar(current, exp->output, dollar));
	while (exp->arg[exp->i] != '\0')
	{
		dollar = 0;
		if (exp->arg[exp->i] == '\'')
			quote = (quote == 0);
		if (exp->arg[exp->i] == '*' && check_star(exp->arg) && quote == 0)
		{
			files = get_files_from_dir(exp->arg);
			if (files_is_null(files, exp))
				return (connect_cur_with_cur(current, files, exp->output));
		}
		filter_quote(exp);
	}
	return (check_output_dollar(current, exp->output, dollar));
}