/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:33 by schuah            #+#    #+#             */
/*   Updated: 2022/10/03 10:02:05 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TEMPORARY FOR DEBUGGING PURPOSES
void	print_cmd_list(t_cmd_list *cmd_list);

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

static t_cmd_list	*ms_get_cmd_list(t_main *main, char *input)
{
	t_parser	*parser;
	t_cmd_list	*cmd_list;

	parser = ms_parser_init(ms_lexer_init(ft_strdup(input)));
	cmd_list = ms_parser_parse_cmd_list(parser);
	main->syntax_error = parser->syntax_error;
	ms_parser_free(&parser);
	return (cmd_list);
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
	t_main		main;
	t_cmd_list	*cmd_list;
	t_executor	*exec;
	char		*input;
	// t_list		*args;

	init_signal();
	init_main(&main, envp);
	while (1)
	{
		// i = 0;
		input = readline("$> ");
		if (input == NULL)
			main.func[MS_EXIT](&main, NULL);
		if (ft_strlen(input) == 0)
			continue ;
		add_history(input);
		if (ms_check_dangling(input))
			continue ;
		cmd_list = ms_get_cmd_list(&main, input);
		ms_expander_cmd_list(&main, cmd_list);
		exec = ms_executor_init();
		ms_heredoc_cmd_list_enqueue(exec, cmd_list);
		ms_executor_cmd_list(&main, exec, cmd_list);
		// args = ft_array_to_list(command, i, sizeof(char *));
		// expander(&main, &args);
		// free_doublearray(command);
		// command = ft_list_to_array(args, sizeof(char *));
		// executor(&main, command);
		// free_doublearray(command);
		// print_cmd_list(cmd_list);
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
