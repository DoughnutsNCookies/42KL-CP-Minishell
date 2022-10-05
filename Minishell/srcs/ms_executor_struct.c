/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 03:10:50 by maliew            #+#    #+#             */
/*   Updated: 2022/10/06 00:54:12 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_executor	*ms_executor_init(void)
{
	t_executor	*exec;

	exec = ft_calloc(1, sizeof(t_executor));
	exec->heredoc = NULL;
	exec->pipe_fd = ft_calloc(2, sizeof(int *));
	exec->pipe_fd[0] = ft_calloc(2, sizeof(int));
	exec->pipe_fd[1] = ft_calloc(2, sizeof(int));
	exec->infile = 0;
	exec->outfile = 1;
	exec->tmpstdin = dup(0);
	exec->tmpstdout = dup(1);
	exec->runtime_error = 0;
	pipe(exec->pipe_fd[0]);
	pipe(exec->pipe_fd[1]);
	return (exec);
}
