/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:19:28 by maliew            #+#    #+#             */
/*   Updated: 2022/10/11 22:22:10 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_expander_delete_null(t_list **list)
{
	t_list	*curr;

	if (list == NULL || *list == NULL)
		return ;
	curr = *list;
	if (*(char **)curr->content == NULL)
	{
		*list = curr->next;
		free(curr->content);
		free(curr);
		curr = NULL;
		ms_expander_delete_null(list);
	}
	else if (**(char **)curr->content == 0)
	{
		*list = curr->next;
		free(*(char **)curr->content);
		free(curr->content);
		free(curr);
		curr = NULL;
		ms_expander_delete_null(list);
	}
	curr = *list;
	if (curr)
		ms_expander_delete_null(&curr->next);
}
