/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:04:30 by schuah            #+#    #+#             */
/*   Updated: 2022/10/17 17:04:27 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether there is a cd command. If no, return 0 . If yes, then
 * will change current directory and return 1. If changing directory fails, throw
 * error and exit with status 1
 * 
 * @param main Main struct containing the environment array
 * @param args Arguments that will be cd into
 * @return int 0 on success
 */
int	cd(t_main *main, char **args)
{
	char	*path;

	if (args[1] == 0)
	{
		path = get_envp_value(main->envp, "HOME");
		if (path == NULL)
			ft_dprintf(STDERR_FILENO, "HOME not set\n");
		else if (chdir(path) < 0)
			perror(path);
		free(path);
	}
	else if (chdir(args[1]) < 0)
		perror(args[1]);
	return (0);
}
