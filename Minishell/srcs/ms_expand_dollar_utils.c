/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_dollar_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:50:30 by maliew            #+#    #+#             */
/*   Updated: 2022/10/18 11:43:23 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Expands the $ symbol by finding its value. Gets the key from the arg
 * and use the key to loop through every environment variable from main to find a
 * matching key
 * 
 * @param main Main struct containing the environement array
 * @param arg Argument containing the key
 * @return char* value if a matching key is found, else returns NULL 
 */
char	*dlr_val(t_main *main, char *arg)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (is_charset(arg[i], "\' \" $ * :", 1, 1) == 0)
		i++;
	key = ft_calloc(i, sizeof(char));
	key[--i] = '\0';
	while (--i >= 0)
		key[i] = arg[i + 1];
	value = get_envp_value(main->envp, key);
	free(key);
	return (value);
}

/**
 * @brief Checks whether there is anything inside the ""
 * 
 * @param exp Expansion struct containing the argument, i position and
 * output string
 * @return int 1 if there is, else 0
 */
int	val_in_quote(t_expand *exp)
{
	int	wc;
	int	i;

	i = exp->i;
	wc = 0;
	while (exp->arg[i + 1] != '\0' && exp->arg[i + 1] != '\"')
	{
		wc++;
		i++;
	}
	return (wc > 0);
}

/**
 * @brief Strjoins the value of $ to the current output
 * 
 * @param exp Expansion struct containing the argument, i position and
 * output string
 * @param d_value Value of $ expanded
 * @return int 0
 */
int	strjoin_n_return(t_expand *exp, char *d_value)
{
	exp->output = ft_strjoin_free(exp->output, d_value);
	free(d_value);
	return (0);
}
