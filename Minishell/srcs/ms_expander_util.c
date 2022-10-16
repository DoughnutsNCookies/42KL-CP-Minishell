/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:19:28 by maliew            #+#    #+#             */
/*   Updated: 2022/10/16 16:07:50 by maliew           ###   ########.fr       */
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
	curr = *list;
	if (curr)
		ms_expander_delete_null(&curr->next);
}

int	is_space_only(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	return (str[i] == '\0');
}
