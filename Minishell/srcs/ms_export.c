/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:29:20 by schuah            #+#    #+#             */
/*   Updated: 2022/09/30 19:38:53 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Adds a new key and value to the existing envp. Calloc a new array with
 * existing size + 2. If value is '\0' (NOT TO BE CONFUSED WITH 0), new envp
 * is KEY="". If value is 0, new envp is KEY. Else, new envp is KEY=VALUE. Copy
 * the rest and frees the old one, sets the new one as the current one
 * 
 * @param main The main struct containing envp
 * @param key The key of the new variable
 * @param value The value of the new variable
 * @param i The position of the last variable in the existing envp + 1
 */
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

/**
 * @brief Replaces the existing envp with the new value. If there is no value and
 * option is set to 1, replace existing envp with new key + no value. Else,
 * replace existing envp with key + '=' + value
 * 
 * @param envp The environment variable list
 * @param key The key of the existing variable
 * @param value The new value of the existing variable
 * @param option Whether the strdup or strjoin is needed to be used
 */
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

/**
 * @brief Loops through existing envp to find whether the key exists. If found,
 * update the key and return. First if statement is for when existing envp is
 * KEY=VALUE (opt 1). Second if statement is for when existing envp is key only
 * (opt 0). If there is already an existing key and arg is key only, return. If
 * no existing key is found, add new key and value to the envp
 * 
 * @param main The main struct containing envp
 * @param args The arguments
 * @param key The key of the "new" variable
 * @param value The value of the "new" variable
 */
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

/**
 * @brief Loops through every args. Check whether the arg is valid. Split the
 * arg into Key and Value, then feed into update_envp function
 * 
 * @param main The main struct containing envp
 * @param args The arguments
 */
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
		else
			free_doublearray(split);
	}
}

/**
 * @brief If export is called with no other args, print envp. Else, add new
 * args into envp
 * 
 * @param main The main struct containing envp
 * @param args The arguments
 * @return int 0 on success
 */
int	export(t_main *main, char **args)
{
	char	**dup;

	if (args[1] == 0 || args[1][0] == '#')
	{
		dup = sort_doublearray(main->envp);
		print_envp(dup);
		free_doublearray(dup);
	}
	else
		find_and_add(main, args);
	return (0);
}
