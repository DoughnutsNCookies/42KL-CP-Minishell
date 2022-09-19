/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:25:03 by schuah            #+#    #+#             */
/*   Updated: 2022/09/19 18:53:11 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Iterate through the args and finds the first '-' character
** Check whether it is a valid flag and only 'n' flag exists in the user input
** Loops through again for cases where the input is (echo -nn -nn Hi)
** Returns the total flag count */
static int	get_flag(char **args)
{
	int	i;
	int	j;
	int	flag_count;

	i = 0;
	flag_count = 0;
	while (args[++i] != 0)
	{
		j = 1;
		if (args[i][0] == '-')
			while (args[i][j] == 'n')
				j++;
		if (args[i][j - 1] == 'n' && args[i][j] == '\0')
			flag_count++;
		else
			break ;
	}
	return (flag_count);
}

/* Gets the "-n" flag count from args
** Using i starting from flag count, iterate through the rest of args and
** print out all the variable. If flag_count is 0, prints out a "\n" */
int	echo(t_main *main, char **args)
{
	int	i;
	int	flag_count;

	if (args[1] == 0)
		return (printf("\n"));
	flag_count = get_flag(args);
	i = flag_count;
	while (args[++i] != 0)
	{
		ft_printf(args[i]);
		if (args[i + 1] != 0)
			ft_printf(" ");
	}
	if (flag_count == 0)
		printf("\n");
	return (0);
	(void)main;
}
