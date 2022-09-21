/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:29:20 by schuah            #+#    #+#             */
/*   Updated: 2022/09/21 21:15:10 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Adds a new key and value to the existing envp
** Calloc a new array with existing size + 2
** (1 for new key + value, 1 for 0, guard)
** If value is '\0' (NOT TO BE CONFUSED WITH 0), new envp is "key="
** If value is 0, new envp is "key"
** Else, new envp is "key=value
** Copy the rest and frees the old one, sets the new one as the current one */
static void	add_new_envp(t_main *main, char *key, char *value, int i)
{
	char	**new_envp;
	char	*temp;

	new_envp = ft_calloc(i + 2, sizeof(char *));
	if (value != 0 && value[0] == '\0')
		new_envp[i] = ft_strjoin(key, "=");
	else if (value == 0)
		new_envp[i] = ft_strdup(key);
	else
	{
		temp = ft_strjoin(key, "=");
		new_envp[i] = ft_strjoin(temp, value);
		free(temp);
	}
	while (--i >= 0)
		new_envp[i] = ft_strdup(main->envp[i]);
	free_doublearray(main->envp);
	main->envp = new_envp;
}

/* Replaces the existing envp with the new value
** If there is no value and option is set to 1,
** replace existing envp with new key + no value
** Else, replace existing envp with key + '=' + value */
static void	do_replace(char **envp, char *key, char *value, int option)
{
	char	*temp;

	free(*envp);
	temp = ft_strjoin(key, "=");
	if (value == 0 && option == 1)
		*envp = ft_strdup(key);
	else
		*envp = ft_strjoin(temp, value);
	free(temp);
}

/* Loops through existing envp to find whether the key exists
** If found, update the key and return
** First if statement is for when existing envp is a="something" (opt 1)
** Second if statement is for when existing envp is key only (opt 0)
** If there is already an existing key and arg is key only, return
** If no existing key is found, add new key and value to the envp */
static void	update_envp(t_main *main, char *args, char *key, char *value)
{
	int		i;

	i = -1;
	while (main->envp[++i] != 0)
	{
		if (ft_strncmp(main->envp[i], key, ft_strlen(key)) == 0
			&& main->envp[i][ft_strlen(key)] == '=')
		{
			if (ft_strlen(args) == ft_strlen(key))
				return ;
			do_replace(&main->envp[i], key, value, 1);
			return ;
		}
		else if (ft_strncmp(main->envp[i], key, ft_strlen(key) + 1) == 0)
		{
			if (ft_strlen(args) == ft_strlen(key))
				return ;
			do_replace(&main->envp[i], key, value, 0);
			return ;
		}
	}
	add_new_envp(main, key, value, i);
}

/* Loops through every args 
** Check whether the arg is valid
** Split the arg into Key and Value, then feed into update_envp function */
static void	find_and_add(t_main *main, char **args)
{
	int		i;
	char	**split;

	i = 0;
	while (args[++i] != 0)
	{
		split = envp_split(args[i]);
		if (check_valid_identifier(args[i], split[0], "export") == 0)
		{
			update_envp(main, args[i], split[0], split[1]);
			free_doublearray(split);
		}
	}
}

/* If export is called with no other args, print envp
** Else, add new args into envp */
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
