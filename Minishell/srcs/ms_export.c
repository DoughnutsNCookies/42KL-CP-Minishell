/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:29:20 by schuah            #+#    #+#             */
/*   Updated: 2022/09/19 22:17:52 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_envp(t_main *main, char *key, char *value)
{
	int		i;
	char	*temp;
	char	**new_envp;

	i = -1;
	while (main->envp[++i] != NULL)
	{
		if (ft_strncmp(main->envp[i], key, ft_strlen(key)) == 0
			&& main->envp[i][ft_strlen(key)] == '=')
		{
			free(main->envp[i]);
			temp = ft_strjoin(key, "=");
			main->envp[i] = ft_strjoin(temp, value);
			free(temp);
			break ;
		}
	}
	new_envp = ft_calloc(i + 2, sizeof(char *));
	temp = ft_strjoin(key, "=");
	if (value == NULL)
		new_envp[i] = temp;
	else
	{
		new_envp[i] = ft_strjoin(temp, value);
		free(temp);
	}
	while (--i >= 0)
		new_envp[i] = ft_strdup(main->envp[i]);
	free_doublearray(main->envp);
	main->envp = new_envp;
}

/* Need to update exit status number */
static void	find_and_add(t_main *main, char **arg)
{
	int		i;
	char	**split;

	i = 0;
	while (arg[++i] != 0)
	{
		split = envp_split(arg[i]);
		if (split == NULL)
		{
			update_envp(main, arg[i], NULL);
		}
		else if (check_valid_identifier(split[0]) == 0)
		{
			update_envp(main, split[0], split[1]);
			free_doublearray(split);
		}
	}
	return ;
}

/* Checks whether default export is called or not */
int	export(t_main *main, char **args)
{
	char	**dup;

	if (args[1] == 0 || args[1][0] == '#')
	{
		dup = sort_envp(main->envp);
		print_envp(dup);
	}
	else
		find_and_add(main, args);
	return (0);
}
