/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:43:45 by maliew            #+#    #+#             */
/*   Updated: 2022/10/12 11:57:06 by schuah           ###   ########.fr       */
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
	while (++i < MS_MAX_BIFUNC)
	{
		if (ft_strcmp(command, cmds[i]) == 0)
			res = 1;
	}
	free_doublearray(cmds);
	return (res);
}

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

void	ms_exec_redir_set(t_exe *exec, t_pipe_list *p)
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

void	ms_executor(t_main *main, t_exe *exec, t_pipe_list *p)
{
	char	**argv;

	ms_exec_redir_set(exec, p);
	expander(main, &p->argv);
	ms_expander_delete_null(&p->argv);
	ft_lstadd_back(&p->argv, ft_lstnew(ft_calloc(1, sizeof(char *))));
	argv = ft_list_to_array(p->argv, sizeof(char *));
	if (ms_exec_is_builtin(argv[0]))
		executor(main, argv);
	else
		exe_non_bi(main, exec, p, argv);
	free(argv);
	ms_exec_redir_reset(exec);
}
