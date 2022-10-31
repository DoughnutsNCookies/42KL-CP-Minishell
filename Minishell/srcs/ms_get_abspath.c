/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_abspath.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 06:55:29 by maliew            #+#    #+#             */
/*   Updated: 2022/10/31 15:57:38 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Combines the command with all the directories in $PATH by looping
 * through and joining them with the command to test for accessibility. If
 * access is granted (i.e. the command is found in one of the path), return the
 * newly joined string, else return the original command
 * 
 * @param paths Paths of $PATH to check with
 * @param rawcmd Original command that will be strjoined with paths to be checked
 * @return char* strjoined command with path if it exists, else return original
 * command 
 */
static char	*comb_cmd(char **paths, char *rawcmd)
{
	char	*cmd;
	char	*temp;

	if (access(rawcmd, F_OK) == 0)
		return (rawcmd);
	while (*paths != NULL)
	{
		temp = ft_strjoin(*paths, "/");
		cmd = ft_strjoin(temp, rawcmd);
		if (access(cmd, F_OK) == 0)
		{
			free(temp);
			return (cmd);
		}
		free(cmd);
		free(temp);
		paths++;
	}
	return (rawcmd);
}

/**
 * @brief Gets the absolute path of a command (e.g. cat -> /bin/cat). If a
 * command is not found in one of the paths in $PATH, the command is not changed
 * 
 * @param envp Environment variables
 * @param cmd Command that will be checked
 * @return int 1 if $PATH is not set
 */
int	ms_get_abspath(char **envp, char **cmd)
{
	char	**split;
	char	*converted;
	char	*temp;
	char	*path;

	temp = *cmd;
	path = ms_get_envp_value(envp, "PATH");
	if (path == NULL)
		return (1);
	split = ft_split(path, ':');
	free(path);
	converted = comb_cmd(split, temp);
	ms_free_doublearray(split);
	if (converted != temp)
	{
		free(*cmd);
		*cmd = converted;
	}
	return (0);
}
