/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:04:30 by schuah            #+#    #+#             */
/*   Updated: 2022/09/09 12:01:00 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cd_command(char *command, char *path)
{
	if (ft_strncmp(command, "cd", 3) != 0)
		return (0);
	if (chdir(path) < 0)
		perror(path);
	return (1);
}
