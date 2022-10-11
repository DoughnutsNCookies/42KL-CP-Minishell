/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_dangling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 00:53:05 by maliew            #+#    #+#             */
/*   Updated: 2022/10/11 14:41:16 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>

/**
 * @brief Checks string for uneven or dangling brackets
 * 
 * @param str String to check
 * @param open Open character
 * @param close Close character
 * @return int 0 if no dangling brackets, >0 if more open than close, <0 if more
 * close than open
 */
static int	ms_has_dangling_bracket(char *str, char open, char close)
{
	int	i;

	i = 0;
	while (*str)
	{
		i += (*str == open) - (*str == close);
		str++;
	}
	return (i);
}

/**
 * @brief Checks string for uneven or dangling quotes
 * 
 * @param str String to check
 * @param c Character to check
 * @return int 0 if no dangling quotes, 1 if there is a dangling quote
 */
static int	ms_has_dangling_quote(char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i = !i;
		str++;
	}
	return (i);
}

/**
 * @brief 	Checks string for dangling single quotes ', dangling double quotes ",
 * and dangling parentheses (). Prints error if there are dangling chars.
 * 
 * @param str String to check
 * @return int 0 if there is no dangling characters, else 1
 */
int	ms_check_dangling(char *str)
{
	int	res;

	res = 0;
	if (ms_has_dangling_quote(str, '\''))
	{
		res = 1;
		ft_dprintf(2, "minishell: syntax error dangling single quote\n");
	}
	else if (ms_has_dangling_quote(str, '"'))
	{
		res = 1;
		ft_dprintf(2, "minishell: syntax error dangling double quote\n");
	}
	else if (ms_has_dangling_bracket(str, '(', ')'))
	{
		res = 1;
		ft_dprintf(2, "minishell: syntax error dangling bracket\n");
	}
	return (res);
}
