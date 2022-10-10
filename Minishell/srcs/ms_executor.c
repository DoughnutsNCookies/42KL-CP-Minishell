/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:33:40 by schuah            #+#    #+#             */
/*   Updated: 2022/10/10 11:01:27 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Loops through the available builtins function and find a match based
 * on args. If found, it will executes the functio. Else write error and set
 * errno to 127
 * 
 * @param main The main struct containing the builtin functions and
 * their respective names
 * @param command The command that will be executed
 */
void	executor(t_main *main, char **command)
{
	int	i;

	i = -1;
	while (++i < MS_MAX_BIFUNC)
	{
		if (command[0] == 0)
			return ;
		if (ft_strcmp(command[0], main->func_name[i]) == 0)
		{
			g_global.error_no = main->func[i](main, command);
			return ;
		}
	}
	ft_dprintf(STDERR_FILENO, "%s: command not found\n", command[0]);
	g_global.error_no = 127;
}

static void	ms_child_close_fd(t_executor *exec, t_pipe_list *p)
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

void	executor_non_builtin(t_main *main, t_executor *exec, t_pipe_list *p,
	char **argv)
{
	int	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		ms_child_close_fd(exec, p);
		if (ms_get_path_env(main->envp, argv))
		{
			free(argv);
			exit(127);
		}
		execve(argv[0], argv, main->envp);
		ft_dprintf(STDERR_FILENO, "%s: command not found\n", argv[0]);
		exit(127);
	}
}
