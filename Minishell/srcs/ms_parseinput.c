/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parseinput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:16:58 by schuah            #+#    #+#             */
/*   Updated: 2022/09/28 11:59:50 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief ft_split the input by ' '. If no input (ie. Ctrl-D), print exit and
 * exit with status 0. If command is exit, print exit and exit with status 0
 * 
 * @param main The main struct containing the exit builtin function
 * @param input The input from readline
 * @return char** string array that are null terminated by 0
 */
char	**parse_input(t_main *main, char *input)
{
	char	**command;
	int		i;

	if (input == 0)
		main->func[MS_EXIT](main, NULL);
	command = ft_split(input, ' ');
	i = -1;
	while (command[++i] != 0)
	{
		if (ft_strncmp(command[i], "exit", 5) == 0)
			main->func[MS_EXIT](main, NULL);
	}
	return (command);
}
