/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 00:36:37 by maliew            #+#    #+#             */
/*   Updated: 2022/10/03 01:51:17 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_heredoc_enqueue(t_list **heredoc, char *delimiter)
{
	char	*buffer;
	int		*fd;

	fd = ft_calloc(2, sizeof(int));
	pipe(fd);
	ft_printf("> ");
	buffer = get_next_line(0);
	while (buffer)
	{
		if (!ft_strncmp(delimiter, buffer, ft_strlen(buffer) - 1)
			&& (ft_strlen(delimiter) == ft_strlen(buffer) - 1))
		{
			free(buffer);
			break ;
		}
		ft_dprintf(fd[1], buffer, ft_strlen(buffer));
		free(buffer);
		ft_printf("> ");
		buffer = get_next_line(0);
	}
	close(fd[1]);
	ft_lstadd_back(heredoc, ft_lstnew(fd));
}

int	ms_heredoc_dequeue(t_list **heredoc)
{
	int		res;
	t_list	*temp;

	temp = *heredoc;
	*heredoc = (*heredoc)->next;
	res = *(int *)temp->content;
	ft_lstdelone(temp, &free);
	return (res);
}