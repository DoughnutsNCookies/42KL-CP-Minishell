/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:43:45 by maliew            #+#    #+#             */
/*   Updated: 2022/10/22 16:15:00 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether the command is a builtin
 * 
 * @param command The command that will be checked
 * @return int 1 if it is a builtin, else 0
 */
int	ms_exec_is_builtin(char *command)
{
	char	**cmds;
	int		i;
	int		res;

	cmds = ft_split("echo cd pwd export unset env exit", ' ');
	i = -1;
	res = 0;
	while (++i < MS_MAX_BIFUNC)
	{
		if (ft_strcmp(command, cmds[i]) == 0)
			res = 1;
	}
	free_doublearray(cmds);
	return (res);
}

/**
 * @brief Resets and closes any fd redirections
 * 
 * @param exec Executor linked list containing the file fds
 */
void	ms_exec_redir_reset(t_exe *exec)
{
	if (exec->pipe_count != 0)
	{
		close(exec->pipe_fd[exec->pipe_count - 1][0]);
		close(exec->pipe_fd[exec->pipe_count - 1][1]);
	}
	if (exec->infile != 0)
		close(exec->infile);
	if (exec->outfile != 1)
		close(exec->outfile);
	dup2(exec->tmpstdin, 0);
	dup2(exec->tmpstdout, 1);
}

/**
 * @brief Redirects the file fds
 * 
 * @param exec Executor linked list containing the file fds
 * @param p Pipe linked list to check if there is next
 */
void	ms_exec_redir_set(t_exe *exec, t_pipe *p)
{
	if (p->next)
		pipe(exec->pipe_fd[exec->pipe_count]);
	if (exec->infile != 0)
		dup2(exec->infile, 0);
	else if (exec->pipe_count != 0)
		dup2(exec->pipe_fd[exec->pipe_count - 1][0], 0);
	if (exec->outfile != 1)
		dup2(exec->outfile, 1);
	else if (p->next)
		dup2(exec->pipe_fd[exec->pipe_count][1], 1);
}

/**
 * @brief Executes the commands. Sets redirection first and then expands the
 * arguments. Executes the command if it is a builtin function. Else executes
 * it directly through another function. Resets and closes any fd redirections
 * in the end.
 * 
 * @param main Main struct containing the environment array
 * @param exec Executor linked list containing the file fds
 * @param p Pipe linked list to check if there is next
 */
void	ms_executor(t_main *main, t_exe *exec, t_pipe *p)
{
	char	**argv;

	ms_exec_redir_set(exec, p);
	expander(main, &p->argv);
	ms_expander_delete_null(&p->argv);
	ft_lstadd_back(&p->argv, ft_lstnew(ft_calloc(1, sizeof(char *))));
	argv = ft_list_to_array(p->argv, sizeof(char *));
	if (argv[0] != NULL && ms_exec_is_builtin(argv[0]))
		executor(main, argv);
	else if (argv[0] != NULL)
	{
		exe_non_bi(main, exec, p, argv);
		exec->has_child = 1;
	}
	free(argv);
	ms_exec_redir_reset(exec);
}
