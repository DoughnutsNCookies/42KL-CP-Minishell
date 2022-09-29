/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:58:16 by schuah            #+#    #+#             */
/*   Updated: 2022/09/29 11:35:29 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints out everyline in environment list
 * 
 * @param main The main struct containing envp
 * @param args The arguments (Can be NULL)
 * @return int 0 on success
 */
int	env(t_main *main, char **args)
{
	int		i;
	char	**split;

	i = -1;
	while (main->envp[++i] != 0)
	{
		split = envp_split(main->envp[i]);
		if (split[1] != 0)
			ft_printf("%s\n", main->envp[i]);
		free_doublearray(split);
	}
	return (0);
	(void)args;
}
