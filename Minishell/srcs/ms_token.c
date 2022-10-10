/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:34:26 by maliew            #+#    #+#             */
/*   Updated: 2022/09/30 02:12:19 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Inits token node.
 * 
 * @param type Token type.
 * @param value Token value.
 * @return t_token* Returns malloced token node.
 */
t_token	*ms_token_init(int type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->e_type = type;
	token->value = value;
	return (token);
}

/**
 * @brief Frees token struct and sets pointer to NULL.
 * 
 * @param token Pointer to pointer to token struct.
 */
void	ms_token_free(t_token **token)
{
	free(*token);
	*token = NULL;
}
