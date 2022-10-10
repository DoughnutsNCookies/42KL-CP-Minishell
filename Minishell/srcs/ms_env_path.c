/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 06:55:29 by maliew            #+#    #+#             */
/*   Updated: 2022/10/10 07:19:45 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*comb_cmd(char **lastcmd, char *newcmd)
{
	char	*cmd;
	char	*temp;

	if (access(newcmd, F_OK) == 0)
		return (newcmd);
	while (*lastcmd != NULL)
	{
		temp = ft_strjoin(*lastcmd, "/");
		cmd = ft_strjoin(temp, newcmd);
		if (access(cmd, F_OK) == 0)
		{
			free(temp);
			return (cmd);
		}
		free(cmd);
		free(temp);
		lastcmd++;
	}
	return (newcmd);
}

int	ms_get_path_env(char **envp, char **cmd)
{
	char	**split;
	char	*converted;
	char	*abs;
	char	*path;

	abs = *cmd;
	path = get_envp_value(envp, "PATH");
	if (path == NULL)
	{
		ft_dprintf(2, "%s: No such file or directory\n", *cmd);
		return (1);
	}
	split = ft_split(path, ':');
	converted = comb_cmd(split, abs);
	if (converted != abs)
	{
		free(*cmd);
		*cmd = converted;
	}
	return (0);
}
