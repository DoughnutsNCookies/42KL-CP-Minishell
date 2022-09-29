/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:04:30 by schuah            #+#    #+#             */
/*   Updated: 2022/09/29 11:36:02 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether there is a cd command. If no, return 0 . If yes, then
 * will change current directory and return 1. If changing directory fails,
 * throw error and exit with status 1
 * 
 * @param main The main struct containing envp
 * @param args The arguments
 * @return int 0 on success
 */
int	cd(t_main *main, char **args)
{
	char	*path;

	if (args[1] == 0)
	{
		path = get_envp_value(main->envp, "HOME");
		if (chdir(path) < 0)
		{
			free(path);
			ft_dprintf(STDERR_FILENO, "cd: HOME not set\n");
		}
		free(path);
	}
	else if (chdir(args[1]) < 0)
		perror(args[1]);
	return (0);
}
