/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_star.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:58:57 by schuah            #+#    #+#             */
/*   Updated: 2022/10/03 16:26:59 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(char *tocheck, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (tocheck[i] == '.')
		return (0);
	while (tocheck[i] != '\0' && arg[j] != '\0')
	{
		if (arg[j] == '*')
		{
			while (arg[j] == '*' && arg[j] != '\0')
				j++;
			if (arg[j] == '\0')
				return (1);
			while (tocheck[i] != '\0' && tocheck[i] != arg[j])
				i++;
			if (tocheck[i] == '\0' && arg[j] != '\0')
				return (0);
			while (tocheck[i] == arg[j])
				i++;
			j++;
			if (arg[j] == '\0' && tocheck[i] != '\0')
				return (0);
			continue ;
		}
		if (arg[j] == tocheck[i])
		{
			i++;
			j++;
		}
		else
			return (0);
		if (arg[j] == '\0' && tocheck[i] != '\0')
			return (0);
	}
	while (arg[j] == '*' && arg[j] != '\0')
		j++;
	if (tocheck[i] == '\0' && arg[j] != '\0')
		return (0);
	return (1);
}

int	check_star(char *arg)
{
	DIR		*dir;

	if (ft_strchr(arg, '*') == NULL)
		return (0);
	dir = get_dir(getcwd(NULL, 0));
	if (dir == NULL)
	{
		ft_dprintf(2, "Cannot open directory\n");
		return (0);
	}
	closedir(dir);
	return (1);
}
