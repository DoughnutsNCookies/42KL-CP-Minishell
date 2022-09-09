/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:04:30 by schuah            #+#    #+#             */
/*   Updated: 2022/09/09 12:10:58 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Checks whether there is a cd command
** If no, return 0
** If yes, then will change current directory and return 1
** If changing directory fails, throw error and exit with status 1
** The directory is changed in the parent instead of in the child */
int	check_cd_command(char *command, char *path)
{
	if (ft_strncmp(command, "cd", 3) != 0)
		return (0);
	if (chdir(path) < 0)
		perror(path);
	return (1);
}
