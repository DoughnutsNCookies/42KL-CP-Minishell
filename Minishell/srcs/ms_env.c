/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:58:16 by schuah            #+#    #+#             */
/*   Updated: 2022/10/31 16:02:40 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints out the environment list
 * 
 * @param main Main struct containing the environment array
 * @param args The arguments (Can be NULL)
 * @return int 0 on success
 */
int	ms_env(t_main *main, char **args)
{
	int		i;
	char	**split;

	i = -1;
	while (main->envp[++i] != 0)
	{
		split = ms_envp_split(main->envp[i]);
		if (split[1] != 0)
			ft_printf("%s\n", main->envp[i]);
		ms_free_doublearray(split);
	}
	return (0);
	(void)args;
}
