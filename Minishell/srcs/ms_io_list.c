/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_io_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:52:47 by maliew            #+#    #+#             */
/*   Updated: 2022/10/17 17:49:44 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Inits IO list with type.
 * 
 * @param type Type to set in IO list struct.
 * @return t_io* Returns a malloced IO list node.
 */
t_io	*ms_io_list_init(int type)
{
	t_io	*io_list;

	io_list = ft_calloc(1, sizeof(t_io));
	io_list->e_type = type;
	io_list->value = NULL;
	io_list->next = NULL;
	return (io_list);
}

/**
 * @brief Parses an IO list node and appends it to the IO list.
 * 
 * @param io_list IO list.
 * @param p Parser struct.
 */
int	ms_parser_parse_io_list(t_io **io_list, t_parser *p)
{
	t_io	*new;
	t_io	*buffer;
	int		type;

	type = p->curr_token->e_type - 3;
	ms_parser_eat(p);
	if (p->curr_token->e_type != TOKEN_WORD)
	{
		ms_parser_syntax_error(p);
		return (1);
	}
	new = ms_io_list_init(type);
	new->value = ft_lstnew(ft_calloc(1, sizeof(char *)));
	ft_memcpy(new->value->content, &p->curr_token->value, sizeof(char *));
	if (*io_list != NULL)
	{
		buffer = *io_list;
		while (buffer->next != NULL)
			buffer = buffer->next;
		buffer->next = new;
	}
	else
		*io_list = new;
	return (0);
}

/** 
 * @brief Checks if token is one of '<<', '>>', '<', '>'
 * 
 * @param token Token to check
 * @return int 1 if token is IO token, 0 if not
 */
int	ms_parser_is_io_token(t_token *token)
{
	return (token->e_type == TOKEN_AIN || token->e_type == TOKEN_AOUT
		|| token->e_type == TOKEN_IN || token->e_type == TOKEN_OUT);
}

/**
 * @brief Frees IO list and its contents.
 * 
 * @param io_list Pointer to pointer of IO list struct.
 */
void	ms_io_list_free(t_io **io_list)
{
	t_io	*temp;

	while (*io_list)
	{
		temp = *io_list;
		*io_list = (*io_list)->next;
		ft_lstclear(&temp->value, &ms_free_args);
		free(temp);
	}
}
