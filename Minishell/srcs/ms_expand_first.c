/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_first.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:01:50 by schuah            #+#    #+#             */
/*   Updated: 2022/10/10 10:25:44 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Converts characters inside "" character by character. If there is a '',
 * convert them to \" instead, if there is a $, expand to their values by
 * appending to the current output. If a * is found, append a ' and the rest of
 * the argument followed by an ending '. If none of the above criteria were met,
 * simply append the character to the current output
 * 
 * @param main The main struct containing the environment list
 * @param exp The expansion struct containing the argument, i position and
 * output string
 */
static void	convert_dquote(t_main *main, t_expand *exp)
{
	while (exp->arg[++exp->i] != '\"')
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
				recurs_expand_dollar(main, exp, 0);
		}
		else if (exp->arg[exp->i] == '*')
		{
			exp->output = append_char(exp->output, '\'');
			while (exp->arg[exp->i] != '\0' && exp->arg[exp->i] != '\"')
				exp->output = append_char(exp->output, exp->arg[exp->i++]);
			exp->output = append_char(exp->output, '\'');
			break ;
		}
		else
			exp->output = append_char(exp->output, exp->arg[exp->i]);
	}
}

/**
 * @brief Converts '', "" and *. If a ' is found, set quote to 1 and append
 * everything as normal character until the next ' is found. If a " is found, it
 * is passed to another function to deal with it. If a * if found and it is
 * inside '', append '*' to the current output
 * 
 * @param main The main struct containing the environment list
 * @param exp The expansion struct containing the argument, i position and
 * output string
 * @param quote Whether there was a single quote
 * @return int 1 if any conversion has been made, else 0
 */
static int	convert_quote_star(t_main *main, t_expand *exp, int *quote)
{
	if (exp->arg[exp->i] == '\'')
	{
		*quote = (*quote == 0);
		exp->i++;
		return (1);
	}
	else if (exp->arg[exp->i] == '\"' && *quote == 0)
	{
		convert_dquote(main, exp);
		exp->i++;
		return (1);
	}
	else if (exp->arg[exp->i] == '*' && *quote == 1)
	{
		exp->output = append_char(exp->output, '\'');
		exp->output = ft_strjoin_free(exp->output, "*\'");
		exp->i++;
		return (1);
	}
	return (0);
}

/**
 * @brief This function will be responsible for converting '', "", * and $ for
 * the second expansion to process and expand. If '', "" and * are found, it is
 * passed to another function to deal with it. If a $ is found, it is expanded 
 * with its values possibly extending the argument linked list.
 * 
 * @param main The main struct containing the environment list
 * @param exp The expansion struct containing the argument, i position and
 * output string
 * @param current The current node of the argument linked list
 * @return t_list* The next node of the argument linked list to be expanded
 */
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
		if (convert_quote_star(main, exp, &quote))
			continue ;
		else if (exp->arg[exp->i] == '$' && quote == 0)
		{
			dollar = expand_dlr(&current, exp,
					dlr_val(main, &exp->arg[exp->i]));
			while (exp->arg[exp->i + 1] != '\0' && exp->arg[exp->i + 1] != '\''
				&& exp->arg[exp->i + 1] != '\"' && exp->arg[exp->i + 1] != '$'
				&& exp->arg[exp->i + 1] != '*')
					exp->i++;
		}
		else
			exp->output = append_char(exp->output, exp->arg[exp->i]);
		exp->i++;
	}
	return (check_output_dollar(current, exp->output, dollar));
}
