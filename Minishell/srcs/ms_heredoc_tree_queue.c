/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc_tree_queue.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:15:23 by maliew            #+#    #+#             */
/*   Updated: 2022/10/17 18:23:17 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Iterates through the IO linked list
 * 
 * @param exec 
 * @param io_list 
 */
static void	ms_heredoc_io_list_dequeue(t_exe *exec, t_io *io_list)
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

/**
 * @brief Iterates through the IO linked list to search for IO_AIN. When found,
 * enqueues the heredoc
 * 
 * @param exec Executor struct containing the heredoc linked list
 * @param io_list IO modifier list struct containing the e_type and delimiter
 */
static void	ms_heredoc_io_list_enqueue(t_exe *exec, t_io *io_list)
{
	while (io_list)
	{
		if (io_list->e_type == IO_AIN)
			ms_heredoc_enqueue(&exec->heredoc,
				*(char **)io_list->value->content);
		io_list = io_list->next;
	}
}

/**
 * @brief Iterate through the pipe linked list to queue each heredoc based on
 * the qtype
 * 
 * @param exec Executor struct containing the heredoc linked list
 * @param pipe_list Pipe linked list that will be iterated through
 * @param qtype Queue type, 0 for dequeue, 1 for enqueue
 */
void	ms_hd_pipe_queue(t_exe *exec, t_pipe *pipe_list, t_qtype qtype)
{
	while (pipe_list)
	{
		if (qtype == 1)
			ms_heredoc_io_list_enqueue(exec, pipe_list->io_list);
		else
			ms_heredoc_io_list_dequeue(exec, pipe_list->io_list);
		pipe_list = pipe_list->next;
	}
}

/**
 * @brief Iterates through the command linked list. If e_type is pipe_list,
 * queues the heredoc based on the qtype, else recurs through this function again
 * with cmd_list->ptr as the cmd_list
 * 
 * @param exec Executor struct containing the heredoc linked list
 * @param cmd_list The command list that will be checked for pipe_list
 * @param qtype Queue type, 0 for dequeue, 1 for enqueue
 */
void	ms_hd_cmd_queue(t_exe *exec, t_cmd *cmd_list, t_qtype qtype)
{
	while (cmd_list)
	{
		if (cmd_list->e_type == PIPE_LIST)
			ms_hd_pipe_queue(exec, cmd_list->ptr, qtype);
		else
			ms_hd_cmd_queue(exec, cmd_list->ptr, qtype);
		cmd_list = cmd_list->next;
	}
}
