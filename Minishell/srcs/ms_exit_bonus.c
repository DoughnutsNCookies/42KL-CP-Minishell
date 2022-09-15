/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:33:28 by schuah            #+#    #+#             */
/*   Updated: 2022/09/15 11:46:26 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Writes out exit message and exits minishell */
int	ms_exit(t_main *main, char **args)
{
	write(1, "exit\n", 5);
	system("leaks -q minishell");
	exit(EXIT_SUCCESS);
	return (0);
	(void)main;
	(void)args;
}
