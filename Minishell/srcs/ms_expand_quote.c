/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:57:56 by schuah            #+#    #+#             */
/*   Updated: 2022/10/05 11:19:07 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Expands single quotes, treats all strings inbetween '' as raw strings
 * 
 * @param arg The argument containing the starting ''
 * @param i The current pos of the argument
 * @param output The output that will house the current node's content
 */
void	expand_squote(t_expand *exp)
{
	while (*(exp->arg + ++exp->i) != '\'' && *(exp->arg + exp->i) != '\0')
		exp->output = append_char(exp->output, *(exp->arg + exp->i));
}

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
void	expand_dquote(t_main *main, t_expand *exp)
{
	char	*dollar_expanded;
	int		j;

	exp->output = append_char(exp->output, '\0');
	while (*(exp->arg + ++exp->i) != '\"' && *(exp->arg + exp->i) != '\0')
	{
		if (*(exp->arg + exp->i) == '$')
		{
			dollar_expanded = dlr_val(main, exp->arg + exp->i);
			j = -1;
			if (dollar_expanded != NULL)
			{
				while (dollar_expanded[++j] != '\0')
					exp->output = append_char(exp->output, dollar_expanded[j]);
			}
			while (exp->arg[exp->i + 1] != '\0' && exp->arg[exp->i + 1] != '\''
				&& exp->arg[exp->i + 1] != '\"' && exp->arg[exp->i + 1] != '$')
				exp->i++;
			free(dollar_expanded);
		}
		else
			exp->output = append_char(exp->output, *(exp->arg + exp->i));
	}
}
