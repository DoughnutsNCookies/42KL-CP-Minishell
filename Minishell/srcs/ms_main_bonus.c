/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:33 by schuah            #+#    #+#             */
/*   Updated: 2022/09/09 12:11:33 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* If readline shows undefined when compiling, you need to install it
** For installation, can check how to at Available Functions
** Every while loop, readline will be called while showing "$> " prompt,
** readline will return user input in char * form
** ft_split the command by " ", and check whether there is a cd command
** If check_cd_command returns 0, then fork out a child to run system program
** Parent will wait for the child before freeing and looping again */
int	main(void)
{
	pid_t	child_pid;
	char	**command;
	char	*input;

	while (1)
	{
		input = readline("$> ");
		if (input == 0)
			break ;
		command = ft_split(input, ' ');
		if (check_cd_command(command[0], command[1]) == 0)
		{
			child_pid = fork();
			if (child_pid < 0)
				perror_and_exit("Fork failed");
			if (child_pid == 0 && execvp(command[0], command) < 0)
				perror_and_exit(command[0]);
			else
				waitpid(child_pid, 0, WUNTRACED);
		}
		free_ftsplit(command);
		free(input);
	}
	system("leaks -q minishell");
	return (0);
}
