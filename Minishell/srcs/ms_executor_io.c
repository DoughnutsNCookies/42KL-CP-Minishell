/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 07:44:48 by maliew            #+#    #+#             */
/*   Updated: 2022/10/11 12:48:47 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints error message if infile and outfile fd are -1 and set runtime
 * error to 1, else return original runtime error 
 * 
 * @param exec Executor struct containing infile fd, outfile fd and runtime
 * error
 * @param filename The file name 
 * @return int runtime error
 */
static int	ms_executor_check_file_error(t_exe *exec, char *filename)
{
	if (exec->infile == -1 || exec->outfile == -1)
	{
		ft_dprintf(2, "minishell: %s: %s\n", filename, strerror(errno));
		exec->runtime_error = 1;
	}
	return (exec->runtime_error);
}

/**
 * @brief Prints error message if the value list is not 1, means the redirection
 * is ambiguous. An example of an ambiguous redirection is where you try to do
 * something like "date > $A", where $A is not defined. If redirection is
 * ambiguous, set runtime error to 1 and return 1, else return 0 only
 * 
 * @param exec Executor struct containing runtime error
 * @param value Value list
 * @param env_val Environment value string
 * @return int 1 if there is an ambiguous redirection, else 0
 */
static int	ms_executor_ambiguous(t_exe *exec, t_list *value, char *env_val)
{
	if (ft_lstsize(value) != 1)
	{
		ft_dprintf(2, "minishell: %s: ambiguous redirect\n", env_val);
		exec->runtime_error = 1;
		return (1);
	}
	return (0);
}

static void	ms_executor_io_in(t_exe *exec, t_io_list *io)
{
	if (exec->infile != 0)
		close(exec->infile);
	if (io->e_type == IO_AIN)
		exec->infile = ms_heredoc_dequeue(&exec->heredoc);
	else
		exec->infile = open(*(char **)io->value->content, O_RDONLY);
}

static void	ms_executor_io_out(t_exe *exec, t_io_list *io)
{
	if (exec->outfile != 1)
		close(exec->outfile);
	if (io->e_type == IO_AOUT)
		exec->outfile = open(*(char **)io->value->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		exec->outfile = open(*(char **)io->value->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

void	ms_executor_io_list(t_main *main, t_exe *exec, t_io_list *io)
{
	char	*env_val;

	while (io)
	{
		if (io->e_type != IO_AIN)
		{
			env_val = ft_strdup(*(char **)io->value->content);
			expander(main, &io->value);
			ms_expander_delete_null(&io->value);
			if (ms_executor_ambiguous(exec, io->value, env_val))
			{
				free(env_val);
				return ;
			}
			free(env_val);
		}
		if (io->e_type == IO_AIN || io->e_type == IO_IN)
			ms_executor_io_in(exec, io);
		else if (io->e_type == IO_AOUT || io->e_type == IO_OUT)
			ms_executor_io_out(exec, io);
		if (ms_executor_check_file_error(exec, *(char **)io->value->content))
			return ;
		io = io->next;
	}
}
