/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:04:30 by schuah            #+#    #+#             */
/*   Updated: 2022/09/23 10:27:47 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks whether there is a cd command
** If no, return 0
** If yes, then will change current directory and return 1
** If changing directory fails, throw error and exit with status 1 */
int	cd(t_main *main, char **args)
{
	char	*path;

	if (args[1] == 0)
	{
		path = get_envp_value(main->envp, "HOME");
		if (chdir(path) < 0)
		{
			free(path);
			write(2, "cd: HOME not set\n", 17);
		}
		free(path);
	}
	else if (chdir(args[1]) < 0)
		perror(args[1]);
	return (1);
	(void)main;
}
