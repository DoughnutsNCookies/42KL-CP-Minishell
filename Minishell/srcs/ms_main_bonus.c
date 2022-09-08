/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:33 by schuah            #+#    #+#             */
/*   Updated: 2022/09/08 21:11:42 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* If readline shows undefined when compiling, you need to install it 
** For installation, can check how to at Available Functions */
int	main(void)
{
	pid_t	child_pid;
	char	**command;
	char	*input;
	int		stat_loc;

	while (1)
	{
		input = readline("$> ");
		command = ft_split(input, ' ');
		if (ft_strncmp(command[0], "cd", 3) == 0)
		{
			if (cd(command[1]) < 0)
				perror(command[1]);
			continue ;
		}
		child_pid = fork();
		if (child_pid < 0)
			perror_and_exit("Fork failed");
		if (child_pid == 0 && execvp(command[0], command) < 0)
			perror_and_exit(command[0]);
		else
			waitpid(child_pid, &stat_loc, WUNTRACED);
	}
	return (0);
}
