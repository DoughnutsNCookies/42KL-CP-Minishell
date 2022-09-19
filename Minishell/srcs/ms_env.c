/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:58:16 by schuah            #+#    #+#             */
/*   Updated: 2022/09/19 18:53:13 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints out everyline in environment list */
int	env(t_main *main, char **args)
{
	int	i;

	i = -1;
	while (main->envp[++i] != 0)
		ft_printf("%s\n", main->envp[i]);
	return (0);
	(void)args;
}
