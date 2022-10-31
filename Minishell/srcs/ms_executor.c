/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:33:40 by schuah            #+#    #+#             */
/*   Updated: 2022/10/31 16:05:46 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Loops through the available builtins function and find a match based
 * on args. If found, it will execute the function
 * 
 * @param main The main struct containing the builtin functions and
 * their respective names
 * @param command The command that will be executed
 */
void	ms_executor_bi(t_main *main, char **command)
{
	int	i;

	i = -1;
	while (++i < MS_MAX_BIFUNC)
	{
		if (ft_strcmp(command[0], main->func_name[i]) == 0)
		{
			g_errno = main->func[i](main, command);
			return ;
		}
	}
}

/**
 * @brief Closes all fd in child process
 * 
 * @param exec Executor linked list containing the file fds
 * @param p Pipe list struct that could be containing the next node to close fd
 */
static void	ms_child_close_fd(t_exe *exec, t_pipe *p)
{
	if (exec->pipe_count != 0)
	{
		close(exec->pipe_fd[exec->pipe_count - 1][0]);
		close(exec->pipe_fd[exec->pipe_count - 1][1]);
	}
	if (p->next)
	{
		close(exec->pipe_fd[exec->pipe_count][0]);
		close(exec->pipe_fd[exec->pipe_count][1]);
	}
}

/**
 * @brief Executes non builtin functions. Sets SIGINT signal back to default and
 * closes all fd in child process. Tries to convert command to absolute path and
 * then executes them with execve. If execve fails it returns, and depending on
 * whether PATH is set, different error messages will be printed out and errno is
 * set to 127
 * 
 * @param main Main struct containing the environment array
 * @param exec Executor linked list containing the file fds
 * @param p Pipe list struct that could be containing the next node to close fd
 * @param argv Argument linked list that will be executed
 */
void	ms_exe_non_bi(t_main *main, t_exe *exec, t_pipe *p, char **argv)
{
	int		pid;
	char	*value;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ms_child_close_fd(exec, p);
		if (argv[0] != NULL && argv[0][0] != '\0')
			ms_get_abspath(main->envp, argv);
		execve(argv[0], argv, main->envp);
		value = ms_get_envp_value(main->envp, "PATH");
		if (value == NULL)
			ft_dprintf(STDERR_FILENO, "%s: No such file or directory\n",
				argv[0]);
		else
			ft_dprintf(STDERR_FILENO, "%s: command not found\n", argv[0]);
		free(value);
		exit(127);
	}
}
