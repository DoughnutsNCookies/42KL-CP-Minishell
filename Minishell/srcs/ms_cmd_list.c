/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cmd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:53:00 by maliew            #+#    #+#             */
/*   Updated: 2022/10/01 19:05:43 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Inits cmd list with operator.
 * 
 * @param operator Operator to set in cmd list struct.
 * @return t_cmd_list* Returns a malloced cmd list node.
 */
t_cmd_list	*ms_cmd_list_init(int operator)
{
	t_cmd_list	*cmd_list;

	cmd_list = ft_calloc(1, sizeof(t_cmd_list));
	cmd_list->e_operator = operator;
	cmd_list->e_type = -1;
	cmd_list->ptr = NULL;
	cmd_list->next = NULL;
	return (cmd_list);
}

/**
 * @brief Appends node to cmd list and moves the buffer to new node.\
 * @brief If e_type is not set, i.e. current cmd list is empty, prints error
 * 			and return.
 * 
 * @param p Parser struct.
 * @param buffer Pointer to cmd list buffer.
 */
static void	ms_parser_cmd_next(t_parser *p, t_cmd_list **buffer)
{
	if ((int)(*buffer)->e_type == -1)
		ms_parser_syntax_error(p);
	else
	{
		(*buffer)->next = ms_cmd_list_init(p->curr_token->e_type);
		*buffer = (*buffer)->next;
		ms_parser_eat(p);
	}
}

/**
 * @brief Sets current node to cmd list and parse the new cmd list.\
 * @brief If e_type is already set, i.e. current cmd list is not empty,
 * 			prints error and return.
 * 
 * @param p Parser struct.
 * @param buffer Pointer to buffer.
 */
static void	ms_parser_cmd_recurse(t_parser *p, t_cmd_list **buffer)
{
	if ((int)(*buffer)->e_type != -1)
		ms_parser_syntax_error(p);
	else
	{
		ms_parser_eat(p);
		(*buffer)->e_type = CMD_LIST;
		(*buffer)->ptr = ms_parser_parse_cmd_list(p);
		ms_parser_eat(p);
	}
}

/**
 * @brief Parses a cmd list.
 * 
 * @param p Parser struct.
 * @return t_cmd_list* Pointer to cmd list head.
 */
t_cmd_list	*ms_parser_parse_cmd_list(t_parser *p)
{
	t_cmd_list	*cmd_list;
	t_cmd_list	*buffer;

	cmd_list = ms_cmd_list_init(OP_START);
	buffer = cmd_list;
	while (p->curr_token && p->syntax_error == 0)
	{
		if (p->curr_token->e_type == TOKEN_LPAREN)
			ms_parser_cmd_recurse(p, &buffer);
		else if (ms_parser_is_pipe_token(p->curr_token))
		{
			buffer->e_type = PIPE_LIST;
			buffer->ptr = ms_parser_parse_pipe_list(p);
		}
		else if (p->curr_token->e_type == TOKEN_AND
			|| p->curr_token->e_type == TOKEN_OR)
			ms_parser_cmd_next(p, &buffer);
		else if (p->curr_token->e_type == TOKEN_NL)
			return (cmd_list);
		else
			break ;
	}
	if ((int)buffer->e_type == -1 && p->syntax_error == 0)
		ms_parser_syntax_error(p);
	return (cmd_list);
}

/**
 * @brief Frees cmd list and its contents.
 * 
 * @param cmd_list Pointer to pointer of cmd list struct.
 */
void	ms_cmd_list_free(t_cmd_list **cmd_list)
{
	t_cmd_list	*temp;

	while (*cmd_list)
	{
		temp = *cmd_list;
		*cmd_list = (*cmd_list)->next;
		if (temp->e_type == PIPE_LIST)
			ms_pipe_list_free((t_pipe_list **)&temp->ptr);
		else
			ms_cmd_list_free((t_cmd_list **)&temp->ptr);
		free(temp);
	}
}