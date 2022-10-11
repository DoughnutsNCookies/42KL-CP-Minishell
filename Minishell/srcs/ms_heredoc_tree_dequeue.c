/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_tree_dequeue.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:15:23 by maliew            #+#    #+#             */
/*   Updated: 2022/10/11 12:11:53 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_heredoc_io_list_dequeue(t_exe *exec, t_io_list *io_list)
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

void	ms_hd_pipe_list_dequeue(t_exe *exec, t_pipe_list *pipe_list)
{
	while (pipe_list)
	{
		ms_heredoc_io_list_dequeue(exec, pipe_list->io_list);
		pipe_list = pipe_list->next;
	}
}

void	ms_hd_cmd_list_dequeue(t_exe *exec, t_cmd_list *cmd_list)
{
	while (cmd_list)
	{
		if (cmd_list->e_type == PIPE_LIST)
			ms_hd_pipe_list_dequeue(exec, cmd_list->ptr);
		else
			ms_hd_pipe_list_dequeue(exec, cmd_list->ptr);
		cmd_list = cmd_list->next;
	}
}
