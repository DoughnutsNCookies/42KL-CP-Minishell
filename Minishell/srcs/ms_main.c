/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:33 by schuah            #+#    #+#             */
/*   Updated: 2022/09/30 17:52:41 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes all of the functions pointers with their respective names
 * and creates a copy of envp and saves it into the struct
 * 
 * @param main The main struct that will be initialized 
 * @param envp The envp from int main()
 */
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

/**
 * @brief Signal will be initialised: Ctrl-\ and Ctrl-C. Every while loop,
 * readline will be called while showing "$> " prompt, and returns user input
 * in char * form, removing the '\n' behind. Then it parses the user input
 * from readline into commands.
 * 
 * @param ac The argument count (Can be NULL)
 * @param av The argument variables (Can be NULL)
 * @param envp The enviroment variable list
 * @return int 0 on success
 */
int	main(int ac, char **av, char **envp)
{
	t_main	main;
	t_list	*args;
	char	**command;
	char	*input;
	int		i;

	// init_signal();
	init_main(&main, envp);
	while (1)
	{
		i = 0;
		input = readline("$> ");
		command = parse_input(&main, input);
		if (input[0] != '\0')
			add_history(input);
		while (command[i] != 0)
			i++;
		args = ft_array_to_list(command, i, sizeof(char *));
		// print_ll(args);
		expander(&main, &args);
		print_ll(args);
		exit(1);
		free_doublearray(command);
		command = ft_list_to_array(args, sizeof(char *));
		executor(&main, command);
		// free_doublearray(command);
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
