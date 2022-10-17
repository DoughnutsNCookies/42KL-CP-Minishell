/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 07:44:48 by maliew            #+#    #+#             */
/*   Updated: 2022/10/17 21:41:13 by schuah           ###   ########.fr       */
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

/**
 * @brief If infile fd is not STDIN, close the fd. If e_type is IO_AIN, dequeue
 * the heredoc. Else open the file and save its fd saved.
 * 
 * @param exec Executor struct containing infile fd and heredoc linked list
 * @param io IO struct containing the name of the file to be opened
 */
static void	ms_executor_io_in(t_exe *exec, t_io *io)
{
	if (exec->infile != STDIN_FILENO)
		close(exec->infile);
	if (io->e_type == IO_AIN)
		exec->infile = ms_heredoc_dequeue(&exec->heredoc);
	else
		exec->infile = open(*(char **)io->value->content, O_RDONLY);
}

/**
 * @brief If infile fd is not STDOUT, close the fd. If e_type is IO_AOUT, open
 * the pile with append mode, if the file do not exist, then create the file.
 * Else truncate the file if it exists, rewriting its contents
 * 
 * @param exec Executor struct containing outfile fd
 * @param io IO struct containing the name of the file to be opened
 */
static void	ms_executor_io_out(t_exe *exec, t_io *io)
{
	if (exec->outfile != STDOUT_FILENO)
		close(exec->outfile);
	if (io->e_type == IO_AOUT)
		exec->outfile = open(*(char **)io->value->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		exec->outfile = open(*(char **)io->value->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

/**
 * @brief Executes the command in IO linked list. If e_type is not IO_AIN, expand
 * the arguments and check if the redirection is ambiguous. If the e_type is
 * IO_AIN or IO_IN, calls a function that opens and reads the file. Else if the
 * e_type is IO_AOUT or IO_OUT, calls a function that opens and save its fd for
 * writing in. If any error occurred (i.e. any fd are < 0), set runtime error to
 * 1 and return
 * 
 * @param main Main struct containing the environment array
 * @param exec Executor struct containing infile fd, outfile fd and heredoc
 * linked list
 * @param io IO struct containing the name of the files to be opened
 */
void	ms_executor_io_list(t_main *main, t_exe *exec, t_io *io)
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
