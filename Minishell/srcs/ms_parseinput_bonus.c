/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parseinput_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 18:16:58 by schuah            #+#    #+#             */
/*   Updated: 2022/09/13 18:59:39 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ft_split the input by ' '
** If no input (ie. Ctrl-D), print exit and exit with status 0
** If command is exit, print exit and exit with status 0 (can be improved) */
char	**parse_input(char *input)
{
	char	**command;
	int		i;

	if (input == 0)
	{
		write(1, "exit\n", 5);
		system("leaks -q minishell");
		exit(0);
	}
	command = ft_split(input, ' ');
	i = -1;
	while (command[++i] != 0)
	{
		if (ft_strncmp(command[i], "exit", 5) == 0)
		{
			write(1, "exit\n", 5);
			system("leaks -q minishell");
			exit(0);
		}
	}
	return (command);
}
