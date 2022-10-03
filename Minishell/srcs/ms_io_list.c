/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_io_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:52:47 by maliew            #+#    #+#             */
/*   Updated: 2022/10/01 16:15:04 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Inits io list with type.
 * 
 * @param type Type to set in io list struct.
 * @return t_io_list* Returns a malloced io list node.
 */
t_io_list	*ms_io_list_init(int type)
{
	t_io_list	*io_list;

	io_list = ft_calloc(1, sizeof(t_io_list));
	io_list->e_type = type;
	io_list->value = NULL;
	io_list->next = NULL;
	return (io_list);
}

/**
 * @brief Parses an io list node and appends it to the io list.
 * 
 * @param io_list Io list.
 * @param p Parser struct.
 */
void	ms_parser_parse_io_list(t_io_list **io_list, t_parser *p)
{
	t_io_list	*new;
	t_io_list	*buffer;

	new = ms_io_list_init(p->curr_token->e_type - 3);
	ms_parser_eat(p);
	if (p->curr_token->e_type != TOKEN_WORD)
		return (ms_parser_syntax_error(p));
	else
	{
		new->value = ft_lstnew(ft_calloc(1, sizeof(char *)));
		ft_memcpy(new->value->content, &p->curr_token->value, sizeof(char *));
	}
	if (*io_list != NULL)
	{
		buffer = *io_list;
		while (buffer->next != NULL)
			buffer = buffer->next;
		buffer->next = new;
	}
	else
		*io_list = new;
}

/** 
 * @brief Checks if token is one of '<<', '>>', '<', '>'
 * 
 * @param token Token to check
 * @return int 1 if token is io token, 0 if not
 */
int	ms_parser_is_io_token(t_token *token)
{
	return (token->e_type == TOKEN_AIN
		|| token->e_type == TOKEN_AOUT
		|| token->e_type == TOKEN_IN
		|| token->e_type == TOKEN_OUT);
}

/**
 * @brief Frees io list and its contents.
 * 
 * @param io_list Pointer to pointer of io list struct.
 */
void	ms_io_list_free(t_io_list **io_list)
{
	t_io_list	*temp;

	while (*io_list)
	{
		temp = *io_list;
		*io_list = (*io_list)->next;
		free(temp->value);
		free(temp);
	}
}
