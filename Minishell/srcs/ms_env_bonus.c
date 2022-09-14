/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:58:16 by schuah            #+#    #+#             */
/*   Updated: 2022/09/14 20:39:34 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_main *main, char **args)
{
	int	i;

	i = -1;
	while (main->envp[++i] != 0)
		ft_printf("%s\n", main->envp[i]);
	return (0);
	(void)args;
}
