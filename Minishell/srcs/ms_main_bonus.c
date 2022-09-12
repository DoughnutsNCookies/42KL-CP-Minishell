/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:33 by schuah            #+#    #+#             */
/*   Updated: 2022/09/12 18:28:20 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Signal will be initialised: Ctrl-\ and Ctrl-C
/* Every while loop, readline will be called while showing "$> " prompt,
** and returns user input in char * form, removing the '\n' behind
** Parses the user input from readline into commands
** If check_cd_command returns 0, then fork out a child to run system program
** Parent will wait for the child before freeing and looping again */
int	main(void)
{
	pid_t	child_pid;
	char	**command;
	char	*input;

	init_signal();
	while (1)
	{
		input = readline("$> ");
		command = parse_input(input);
		if (ft_getwc(input, ' ') < 1)
			continue ;
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
	return (0);
}

/*
char	cmd[] = "/usr/bin/ls";
char	*av[] = {"ls", "-l", NULL};
char	*envp[] = {NULL};

execve(cmd, av, envp); */