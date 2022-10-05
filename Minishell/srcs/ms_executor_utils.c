/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:43:45 by maliew            #+#    #+#             */
/*   Updated: 2022/10/06 02:01:50 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_exec_is_builtin(char *command)
{
	char	**cmds;
	int		i;
	int		res;

	cmds = ft_split("echo cd pwd export unset env exit", ' ');
	i = -1;
	res = 0;
	while (++i < 7)
	{
		if (ft_strcmp(command, cmds[i]) == 0)
			res = 1;
	}
	free_doublearray(cmds);
	return (res);
}

void	ms_exec_redir_reset(t_executor *exec, t_pipe_list *pipe)
{
	if (exec->pipe_count != 0)
		close(exec->pipe_fd[exec->pipe_count % 2 == 0][0]);
	if (pipe->next)
		close(exec->pipe_fd[exec->pipe_count % 2 == 1][1]);
	dup2(exec->tmpstdin, 0);
	dup2(exec->tmpstdout, 1);
}

void	ms_exec_redir_set(t_executor *exec, t_pipe_list *pipe)
{
	if (exec->infile != 0)
		dup2(exec->infile, 0);
	else if (exec->pipe_count != 0)
		dup2(exec->pipe_fd[exec->pipe_count % 2 == 0][0], 0);
	if (exec->outfile != 1)
		dup2(exec->outfile, 1);
	else if (pipe->next)
		dup2(exec->pipe_fd[exec->pipe_count % 2 == 1][1], 1);
}

void	ms_executor(t_main *main, t_executor *exec, t_pipe_list *pipe)
{
	char	**argv;
	int		pid;
	int		status;

	ms_exec_redir_set(exec, pipe);
	ft_lstadd_back(&pipe->argv, ft_lstnew(ft_calloc(1, sizeof(char *))));
	argv = ft_list_to_array(pipe->argv, sizeof(char *));
	if (ms_exec_is_builtin(argv[0]))
		executor(main, argv);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			execve(argv[0], argv, main->envp);
			ft_dprintf(STDERR_FILENO, "%s: command not found\n", argv[0]);
			exit(127);
		}
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			g_global.error_no = WEXITSTATUS(status);
	}
	ms_exec_redir_reset(exec, pipe);
}
