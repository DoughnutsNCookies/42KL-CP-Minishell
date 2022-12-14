/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:31:05 by schuah            #+#    #+#             */
/*   Updated: 2022/10/31 16:04:57 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Calloc a new array with existing size + 1 (1 for 0, guard). Loops
 * through existing envp and finds for matching key. If current string does
 * not match with the key, it is dup into the new envp. If current string
 * matches with the key, it is ignored. Frees the old envp and sets the new
 * one as the current one
 * 
 * @param main Main struct containing the environment array
 * @param key Key of the value that will be deleted
 */
static void	find_and_delete(t_main *main, char *key)
{
	char	**new_envp;
	char	**split;
	int		i;
	int		j;

	i = 0;
	while (main->envp[i] != 0)
		i++;
	new_envp = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (main->envp[++i] != 0)
	{
		split = ms_envp_split(main->envp[i]);
		if (ft_strcmp(split[0], key) != 0)
			new_envp[j++] = ft_strdup(main->envp[i]);
		ms_free_doublearray(split);
	}
	ms_free_doublearray(main->envp);
	main->envp = new_envp;
}

/**
 * @brief Checks whether the arg is valid. If so then find and delete the
 * envp based on the key
 * 
 * @param main Main struct containing the environment array
 * @param args Arguments that will be unset
 * @return int 0 on success, else 1
 */
int	ms_unset(t_main *main, char **args)
{
	int		i;

	i = 0;
	while (args[++i] != 0)
	{
		if (ms_check_valid_identifier(args[i], args[i], "unset") == 0)
			find_and_delete(main, args[i]);
		else
			return (1);
	}
	return (0);
}
