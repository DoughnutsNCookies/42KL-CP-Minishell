/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:29:20 by schuah            #+#    #+#             */
/*   Updated: 2022/09/20 18:42:22 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_envp(t_main *main, char *key, char *value)
{
	int		i;
	char	*temp;
	char	**new_envp;

	i = -1;
	while (main->envp[++i] != 0)
	{
		// ft_printf("\n|%s|\n", main->envp[i]);
		// if (ft_strncmp(main->envp[i], key, ft_strlen(key)) == 0
		// 	&& main->envp[i][ft_strlen(main->envp[i]) - 1] != '=')
		// 	return ;
		if (ft_strncmp(main->envp[i], key, ft_strlen(key) + 1) == 0)
		{
			ft_printf("trigger");
			free(main->envp[i]);
			temp = ft_strjoin(key, "=");
			main->envp[i] = ft_strjoin(temp, value);
			free(temp);
			break ;
		}
		if (ft_strncmp(main->envp[i], key, ft_strlen(key)) == 0
			&& main->envp[i][ft_strlen(key)] == '=')
		{
			ft_printf("trigger");
			free(main->envp[i]);
			temp = ft_strjoin(key, "=");
			main->envp[i] = ft_strjoin(temp, value);
			free(temp);
			break ;
		}
	}
	new_envp = ft_calloc(i + 2, sizeof(char *));
	if (value != NULL)
	{
		if (value[0] == '\0')
		{
			new_envp[i] = ft_strdup(key);
			ft_printf("1NEW: %s\n", new_envp[i]);
		}
		else
		{
			temp = ft_strjoin(key, "=");
			new_envp[i] = ft_strjoin(temp, value);
			free(temp);
			ft_printf("2NEW: %s\n", new_envp[i]);
		}
	}
	else if (value == NULL)
	{
		new_envp[i] = ft_strjoin(key, "=");
		ft_printf("3NEW: %s\n", new_envp[i]);
	}
	new_envp[i + 1] = 0;
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
		if (check_valid_identifier(split[0]) == 0)
		{
			printf("Key: |%s|\n", split[0]);
			printf("Value: |%s|\n", split[1]);
			update_envp(main, split[0], split[1]);
			print_envp(main->envp);
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
