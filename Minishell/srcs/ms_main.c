/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:33 by schuah            #+#    #+#             */
/*   Updated: 2022/09/26 22:08:36 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initializes all of the functions pointers with their respective names
** Creates a copy of envp and saves it into the struct */
static void	init_main(t_main *main, char **envp)
{
	main->func_name = ft_split("echo cd pwd export unset env exit", ' ');
	main->func[MS_ECHO] = echo;
	main->func[MS_CD] = cd;
	main->func[MS_PWD] = pwd;
	main->func[MS_EXPORT] = export;
	main->func[MS_UNSET] = unset;
	main->func[MS_ENV] = env;
	main->func[MS_EXIT] = ms_exit;
	main->envp = dup_doublearray(envp);
}

/* Signal will be initialised: Ctrl-\ and Ctrl-C
** Every while loop, readline will be called while showing "$> " prompt,
** and returns user input in char * form, removing the '\n' behind
** Parses the user input from readline into commands
** If check_cd_command returns 0, then fork out a child to run system program
** Parent will wait for the child before freeing and looping again */
int	main(int ac, char **av, char **envp)
{
	t_main	main;	
	char	**command;
	char	*input;

	init_signal();
	init_main(&main, envp);
	while (1)
	{
		input = readline("$> ");
		command = parse_input(&main, input);
		if (input[0] != '\0')
			add_history(input);
		// command = expander(&main, command);
		executor(&main, command);
		free_doublearray(command);
		free(input);
	}
	return (EXIT_SUCCESS);
	(void)ac;
	(void)av;
}

/*
child_pid = fork();
if (child_pid < 0)
	perror_and_exit("Fork failed");
if (child_pid == 0 && execve(command[0], command, envp) < 0)
	perror_and_exit(command[0]);
else
	waitpid(child_pid, 0, WUNTRACED);

char	cmd[] = "/bin/ls";
char	*av[] = {"ls", "-l", NULL};
char	*envp[] = {NULL};

execve(cmd, av, envp);
*/