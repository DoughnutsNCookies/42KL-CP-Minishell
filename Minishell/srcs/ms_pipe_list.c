/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:52:58 by maliew            #+#    #+#             */
/*   Updated: 2022/10/10 11:11:03 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Inits pipe list.
 * 
 * @return t_pipe_list* Returns a malloced pipe list node.
 */
t_pipe_list	*ms_pipe_list_init(void)
{
	t_pipe_list	*pipe_list;

	pipe_list = ft_calloc(1, sizeof(t_pipe_list));
	pipe_list->argv = NULL;
	pipe_list->io_list = NULL;
	pipe_list->next = NULL;
	return (pipe_list);
}

/**
 * @brief Appends node to pipe list and moves the buffer to new node.\
 * @brief If both argv and io list is empty, i.e. current pipe list is empty,
 * 			prints error and return.
 * 
 * @param p Parser struct.
 * @param buffer Pointer to pipe list buffer.
 */
static void	ms_parser_pipe_next(t_parser *p, t_pipe_list **buffer)
{
	if ((*buffer)->argv == NULL && (*buffer)->io_list == NULL)
		ms_parser_syntax_error(p);
	else
	{
		(*buffer)->next = ms_pipe_list_init();
		*buffer = (*buffer)->next;
	}
}

/**
 * @brief Parses a pipe list.
 * 
 * @param p Parser struct.
 * @return t_pipe_list* Pointer to pipe list head.
 */
t_pipe_list	*ms_parser_parse_pipe_list(t_parser *p)
{
	t_pipe_list	*pipe_list;
	t_pipe_list	*buffer;
	t_list		*new;

	pipe_list = ms_pipe_list_init();
	buffer = pipe_list;
	while (p->curr_token && p->syntax_error == 0)
	{
		if (p->curr_token->e_type == TOKEN_WORD)
		{
			new = ft_lstnew(ft_calloc(1, sizeof(char *)));
			ft_memcpy(new->content, &p->curr_token->value, sizeof(char *));
			ft_lstadd_back(&buffer->argv, new);
		}
		else if (p->curr_token->e_type == TOKEN_PIPE)
			ms_parser_pipe_next(p, &buffer);
		else if (ms_parser_is_io_token(p->curr_token))
			ms_parser_parse_io_list(&buffer->io_list, p);
		else
			break ;
		ms_parser_eat(p);
	}
	if (buffer->argv == NULL && buffer->io_list == NULL)
		ms_parser_syntax_error(p);
	return (pipe_list);
}

/**
 * @brief Checks if token is one of word token, '|', '<<', '>>', '<', '>'
 * 
 * @param token Token to check
 * @return int 1 if token is pipe list token, 0 if not
 */
int	ms_parser_is_pipe_token(t_token *token)
{
	return (token->e_type == TOKEN_WORD
		|| token->e_type == TOKEN_PIPE
		|| ms_parser_is_io_token(token));
}

/**
 * @brief Frees pipe list and its contents.
 * 
 * @param pipe_list Pointer to pointer of pipe list struct.
 */
void	ms_pipe_list_free(t_pipe_list **pipe_list)
{
	t_pipe_list	*temp;

	while (*pipe_list)
	{
		temp = *pipe_list;
		*pipe_list = (*pipe_list)->next;
		ft_lstclear(&temp->argv, &ms_free_args);
		ms_io_list_free(&temp->io_list);
		free(temp);
	}
}
