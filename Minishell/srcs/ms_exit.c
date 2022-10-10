/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:33:28 by schuah            #+#    #+#             */
/*   Updated: 2022/10/10 22:32:00 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Writes out exit message and exits with status 0
 * 
 * @param main The main struct (Can be NULL)
 * @param args The arguments (Can be NULL)
 * @return int 0 on success
 */
int	ms_exit(t_main *main, char **args)
{
	ft_printf("exit\n");
	system("leaks -q minishell");
	exit(EXIT_SUCCESS);
	return (0);
	(void)main;
	(void)args;
}
