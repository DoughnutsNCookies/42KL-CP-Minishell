/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_tree_dequeue.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:15:23 by maliew            #+#    #+#             */
/*   Updated: 2022/10/03 10:16:12 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_heredoc_io_list_dequeue(t_executor *exec, t_io_list *io_list)
{
	int	fd;

	while (io_list)
	{
		if (io_list->e_type == IO_AIN)
		{
			fd = ms_heredoc_dequeue(&exec->heredoc);
			close(fd);
		}	
		io_list = io_list->next;
	}
}

void	ms_heredoc_pipe_list_dequeue(t_executor *exec, t_pipe_list *pipe_list)
{
	while (pipe_list)
	{
		ms_heredoc_io_list_dequeue(exec, pipe_list->io_list);
		pipe_list = pipe_list->next;
	}
}

void	ms_heredoc_cmd_list_dequeue(t_executor *exec, t_cmd_list *cmd_list)
{
	while (cmd_list)
	{
		if (cmd_list->e_type == PIPE_LIST)
			ms_heredoc_pipe_list_dequeue(exec, cmd_list->ptr);
		else
			ms_heredoc_pipe_list_dequeue(exec, cmd_list->ptr);
		cmd_list = cmd_list->next;
	}
}
