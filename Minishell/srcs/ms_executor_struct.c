/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 03:10:50 by maliew            #+#    #+#             */
/*   Updated: 2022/10/11 12:11:53 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exe	*ms_executor_init(void)
{
	t_exe	*exec;

	exec = ft_calloc(1, sizeof(t_exe));
	exec->heredoc = NULL;
	exec->pipe_fd = NULL;
	exec->infile = 0;
	exec->outfile = 1;
	exec->tmpstdin = dup(0);
	exec->tmpstdout = dup(1);
	exec->runtime_error = 0;
	return (exec);
}

void	ms_executor_init_pipefd(t_exe *exec, t_pipe_list *p)
{
	int	i;

	i = 0;
	while (p)
	{
		p = p->next;
		i++;
	}
	exec->pipe_fd = ft_calloc(i + 1, sizeof(int *));
	exec->pipe_fd[i] = NULL;
	while (i--)
		exec->pipe_fd[i] = ft_calloc(2, sizeof(int));
}

void	ms_executor_free_pipefd(t_exe *exec)
{
	int	i;

	i = 0;
	while (exec->pipe_fd[i])
	{
		free(exec->pipe_fd[i]);
		i++;
	}
	free(exec->pipe_fd);
	exec->pipe_fd = NULL;
}

void	ms_executor_free(t_exe **exec)
{
	close((*exec)->tmpstdin);
	close((*exec)->tmpstdout);
	free(*exec);
	*exec = NULL;
}
