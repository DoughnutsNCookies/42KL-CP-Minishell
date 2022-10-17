/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:37:21 by maliew            #+#    #+#             */
/*   Updated: 2022/10/17 21:47:49 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returnpid will be returned from waitpid and the status number will be
 * stored as well. IF the WIFEXITED of the status returns true (i.e. the child
 * terminated normally), errno is set to WEXITSTATUS of the status
 * 
 */
void	ms_executor_wait_pipe(void)
{
	int	returnpid;
	int	status;

	returnpid = 1;
	while (returnpid > 0)
		returnpid = waitpid(-1, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_errno = (WEXITSTATUS(status));
}

/**
 * @brief Allocates memory to all the pipe_fd in t_exec. Iterates through the
 * pipe linked list and executes the command based on the IO fds. If there is
 * runtime error, errno is set to that runtime error, else execute the commands.
 * After everything, free the pipe fds and wait for the child process to
 * terminate
 * 
 * @param main Main struct containing the environment array
 * @param exec Executor struct containing infile fd, outfile fd and heredoc
 * linked list
 * @param pipe Pipe linked list
 */
void	ms_executor_pipe_list(t_main *main, t_exe *exec, t_pipe *pipe)
{
	exec->pipe_count = 0;
	ms_executor_init_pipefd(exec, pipe);
	while (pipe)
	{
		exec->infile = 0;
		exec->outfile = 1;
		ms_executor_io_list(main, exec, pipe->io_list);
		if (exec->runtime_error)
			g_errno = exec->runtime_error;
		else
			ms_executor(main, exec, pipe);
		pipe = pipe->next;
		exec->pipe_count++;
	}
	ms_executor_free_pipefd(exec);
	ms_executor_wait_pipe();
}

/**
 * @brief Iterates through the command linked list and executes the arguments.
 * Arguments will be executed based on the operator. For example, START will be
 * executed regardless, AND will be executed if the previous program exited with
 * errno of 0, and OR will be exeted if the previous program exited with errno
 * not 0 (Failed). Else if the e_type is PIPE_LIST, dequeue the heredocs
 * 
 * @param main Main struct containing the environment array
 * @param exec Executor struct containing infile fd, outfile fd and heredoc
 * linked list
 * @param cmd The command linked list
 */
void	ms_executor_cmd_list(t_main *main, t_exe *exec, t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->e_operator == OP_START
			|| (cmd->e_operator == OP_AND && g_errno == 0)
			|| (cmd->e_operator == OP_OR && g_errno != 0))
		{
			if (cmd->e_type == PIPE_LIST)
				ms_executor_pipe_list(main, exec, cmd->ptr);
			else
				ms_executor_cmd_list(main, exec, cmd->ptr);
		}
		else
		{
			if (cmd->e_type == PIPE_LIST)
				ms_hd_pipe_queue(exec, cmd->ptr, DQ);
			else
				ms_hd_cmd_queue(exec, cmd->ptr, DQ);
		}
		cmd = cmd->next;
	}
}
