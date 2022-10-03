/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:21:31 by maliew            #+#    #+#             */
/*   Updated: 2022/09/29 04:37:48 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 	Checks if string has a special token at the start.
 * 			Special tokens are && || << >> < > | ( )
 * 
 * @param s 	String to check
 * @return int 1 if there is a token at the start of the string, 0 if not.
 */
int	ms_lexer_is_spec(char *s)
{
	if (ft_strchr("|<>()", *s))
		return (1);
	if (ft_strncmp(s, "&&", 2) == 0)
		return (1);
	return (0);
}
