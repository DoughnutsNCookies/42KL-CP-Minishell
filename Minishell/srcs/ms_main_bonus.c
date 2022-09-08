/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:33 by schuah            #+#    #+#             */
/*   Updated: 2022/09/08 17:13:53 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**get_input(char *input)
// {
//     char **command = malloc(8 * sizeof(char *));
//     char *separator = " ";
//     char *parsed;
//     int index = 0;

//     parsed = strtok(input, separator);
//     while (parsed != NULL)
// 	{
//         command[index] = parsed;
//         index++;

//         parsed = strtok(NULL, separator);
//     }

//     command[index] = NULL;
//     return command;
// }

int	cd(char *path)
{
	return (chdir(path));
}

/* If readline shows undefined when compiling, you need to install it */
int	main(int ac, char **av, char **envp)
{
	char	**command;
	char	*input;
	pid_t	child_pid;
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
		{
			perror("Fork failed");
			exit(1);
		}
		if (child_pid == 0)
		{
			if (execvp(command[0], command) < 0)
			{
				perror(command[0]);
				exit(1);
			}
			printf("This won't be printed if execve is successful\n");
		}
		else
			waitpid(child_pid, &stat_loc, WUNTRACED);
	}
	ft_printf("Hello World\n");
	return (0);
	(void)ac;
	(void)av;
	(void)envp;
}
