/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:37:21 by maliew            #+#    #+#             */
/*   Updated: 2022/10/10 08:02:49 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_executor_wait_pipe(void)
{
	int	returnpid;
	int	status;

	returnpid = 1;
	while (returnpid > 0)
		returnpid = waitpid(-1, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_global.error_no = (WEXITSTATUS(status));
}

void	ms_executor_pipe_list(t_main *main, t_executor *exec, t_pipe_list *pipe)
{
	exec->pipe_count = 0;
	ms_executor_init_pipefd(exec, pipe);
	while (pipe)
	{
		exec->infile = 0;
		exec->outfile = 1;
		ms_executor_io_list(main, exec, pipe->io_list);
		if (exec->runtime_error)
			g_global.error_no = exec->runtime_error;
		else
			ms_executor(main, exec, pipe);
		pipe = pipe->next;
		exec->pipe_count++;
	}
	ms_executor_free_pipefd(exec);
	ms_executor_wait_pipe();
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
