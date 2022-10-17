/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:42:33 by schuah            #+#    #+#             */
/*   Updated: 2022/10/17 18:21:21 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes all of the functions pointers with their respective names
 * and creates a copy of envp and saves it into the struct
 * 
 * @param main Main struct that will be initialized 
 * @param envp Environment variable array from int main()
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
 * @brief Parses the user input into a linked list for execution
 * 
 * @param main Main struct containing the boolean syntax error
 * @param input User input
 * @return t_cmd* head of the command linked list
 */
static t_cmd	*ms_get_cmd_list(t_main *main, char *input)
{
	t_parser	*parser;
	t_cmd		*cmd_list;

	parser = ms_parser_init(ms_lexer_init(ft_strdup(input)));
	cmd_list = ms_parser_parse_cmd_list(parser);
	main->syntax_error = parser->syntax_error;
	ms_parser_free(&parser);
	return (cmd_list);
}

/**
 * @brief Executes the command linked list in order
 * 
 * @param main Main struct containing the environment array, boolean syntax error
 * and builtin functions
 * @param cmd_list head of the command linked list 
 */
static void	ms_run_execution(t_main *main, t_cmd *cmd_list)
{
	t_exe	*exec;

	exec = ms_executor_init();
	ms_hd_cmd_queue(exec, cmd_list, EQ);
	ms_executor_cmd_list(main, exec, cmd_list);
	ms_executor_free(&exec);
}

/**
 * @brief Signal will be initialised: Ctrl-\ and Ctrl-C every loop, readline will
 * be called while showing the "$> " prompt, and returns user input in char *
 * form, removing the '\n' behind. Then it parses the user input from readline
 * into commands. Adds the input to the history and checks whether it is a valid
 * input. Converts the input into linked list and executes them in order. The
 * linked list is then free and the cycle repeats until exit
 * 
 * @param main Main struct that was initialized
 */
void	ms_read_next_line(t_main *main)
{
	t_cmd	*cmd_list;
	char	*input;

	init_signal();
	input = readline("$> ");
	if (input == NULL)
		main->func[MS_EXIT](NULL, NULL);
	if (ft_strlen(input) != 0)
	{
		add_history(input);
		if (!ms_check_dangling(input))
		{
			cmd_list = ms_get_cmd_list(main, input);
			if (main->syntax_error == 0)
				ms_run_execution(main, cmd_list);
			else
				g_errno = main->syntax_error;
			ms_cmd_list_free(&cmd_list);
		}
	}
	free(input);
}

/**
 * @brief Initializes the main struct and enters a while(1) loop to start
 * minishell
 * 
 * @param ac The argument count (Can be NULL)
 * @param av The argument variables (Can be NULL)
 * @param envp The enviroment variable array
 * @return int 0 on success
 */
int	main(int ac, char **av, char **envp)
{
	t_main		main;

	init_main(&main, envp);
	while (1)
		ms_read_next_line(&main);
	return (EXIT_SUCCESS);
	(void)ac;
	(void)av;
}
