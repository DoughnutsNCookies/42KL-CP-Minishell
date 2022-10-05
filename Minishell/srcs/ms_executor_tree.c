/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:37:21 by maliew            #+#    #+#             */
/*   Updated: 2022/10/06 02:06:09 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_executor_check_error(t_executor *exec, int error)
{
	if (error != 0)
	{
		ft_dprintf(2, "some runtime error\n");
		exec->runtime_error = 1;
	}
	return (error);
}

int	ms_executor_check_ambiguous(t_executor *exec, t_list *value)
{
	if (ft_lstsize(value) != 1)
	{
		ft_dprintf(2, "minishell: ambiguous redirect\n");
		return (ms_executor_check_error(exec, 1));
	}
	return (0);
}

void	ms_executor_io_list(t_executor *exec, t_io_list *io)
{
	while (io)
	{
		if (io->e_type == IO_AIN || io->e_type == IO_IN)
		{
			if (exec->infile != 0)
				close(exec->infile);
			if (io->e_type == IO_AIN)
				exec->infile = ms_heredoc_dequeue(&exec->heredoc);
			else
			{
				if (ms_executor_check_ambiguous(exec, io->value))
					return ;
				exec->infile = open(*(char **)io->value->content, O_RDONLY);
			}
		}
		else if (io->e_type == IO_AOUT || io->e_type == IO_OUT)
		{
			if (exec->outfile != 1)
				close(exec->outfile);
			if (ms_executor_check_ambiguous(exec, io->value))
				return ;
			if (io->e_type == IO_AOUT)
				exec->outfile = open(*(char **)io->value->content,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				exec->outfile = open(*(char **)io->value->content,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (ms_executor_check_error(exec, exec->infile == -1)
			|| ms_executor_check_error(exec, exec->outfile == -1))
			return ;
		io = io->next;
	}
}

void	ms_executor_pipe_list(t_main *main, t_executor *exec, t_pipe_list *pipe)
{
	exec->pipe_count = 0;
	while (pipe)
	{
		exec->infile = 0;
		exec->outfile = 1;
		ms_executor_io_list(exec, pipe->io_list);
		if (exec->runtime_error)
			g_global.error_no = exec->runtime_error;
		else
			ms_executor(main, exec, pipe);
		pipe = pipe->next;
		exec->pipe_count++;
	}
}

void	ms_executor_cmd_list(t_main *main, t_executor *e, t_cmd_list *cmd)
{
	while (cmd)
	{
		if (cmd->e_operator == OP_START
			|| (cmd->e_operator == OP_AND && g_global.error_no == 0)
			|| (cmd->e_operator == OP_OR && g_global.error_no != 0))
		{
			if (cmd->e_type == PIPE_LIST)
				ms_executor_pipe_list(main, e, cmd->ptr);
			else
				ms_executor_cmd_list(main, e, cmd->ptr);
		}
		else
		{
			if (cmd->e_type == PIPE_LIST)
				ms_heredoc_pipe_list_dequeue(e, cmd->ptr);
			else
				ms_heredoc_cmd_list_dequeue(e, cmd->ptr);
		}
		cmd = cmd->next;
	}
}
