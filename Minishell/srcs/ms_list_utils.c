/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:10:09 by maliew            #+#    #+#             */
/*   Updated: 2022/10/10 22:03:27 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ms_cmd_list_parse_pipe_list(t_cmd_list *buffer, t_parser *p)
{
	if ((int)buffer->e_type != -1)
	{
		ms_parser_syntax_error(p);
		return (1);
	}
	buffer->e_type = PIPE_LIST;
	buffer->ptr = ms_parser_parse_pipe_list(p);
	return (0);
}