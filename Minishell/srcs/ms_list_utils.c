/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:10:09 by maliew            #+#    #+#             */
/*   Updated: 2022/10/17 14:57:10 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees the content inside of a linked list's node 
 * 
 * @param content Content that will be freed
 */
void	ms_free_args(void *content)
{
	if (*(char **)content)
		free(*(char **)content);
	free(content);
}

/**
 * @brief Sorts the list in ascii order
 * 
 * @param lst The head of the list
 */
void	ft_lstsort(t_list **lst)
{
	t_list	*current;
	t_list	*nextnode;
	int		sorted;
	void	*temp;

	sorted = 0;
	while (sorted == 0)
	{
		sorted = 1;
		current = *lst;
		nextnode = current;
		while (nextnode->next != NULL)
		{
			if (ft_strcmp(*(char **)nextnode->content,
					*(char **)nextnode->next->content) > 0)
			{
				temp = nextnode->content;
				nextnode->content = nextnode->next->content;
				nextnode->next->content = temp;
				sorted = 0;
			}
			nextnode = nextnode->next;
		}
		current = current->next;
	}
}

/**
 * @brief If there is an error in the buffer, print syntax error and set parser
 * syntax_error to 1. Else set e_type to PIPE_LIST and parses the pipe list.
 * 
 * @param buffer Buffer linked list
 * @param p Parser struct
 * @return int 1 if there is syntax error in parser linked list, else 0
 */
int	ms_cmd_list_parse_pipe_list(t_cmd_list *buffer, t_parser *p)
{
	if ((int)buffer->e_type != -1)
	{
		ms_parser_syntax_error(p);
		return (1);
	}
	buffer->e_type = PIPE_LIST;
	buffer->ptr = ms_parser_parse_pipe_list(p);
	return (p->syntax_error);
}

/**
 * @brief Creates a new node using parser struct as content, and adds it to the
 * back of the buffer linked list
 * 
 * @param buffer Buffer linked list that will be added to the back
 * @param p Parser struct that will be used as content for the new node
 */
void	ms_pipe_new_arg(t_pipe_list *buffer, t_parser *p)
{
	t_list		*new;

	new = ft_lstnew(ft_calloc(1, sizeof(char *)));
	ft_memcpy(new->content, &p->curr_token->value, sizeof(char *));
	ft_lstadd_back(&buffer->argv, new);
}
