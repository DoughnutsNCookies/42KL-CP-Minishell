/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:31:05 by schuah            #+#    #+#             */
/*   Updated: 2022/10/10 10:21:19 by schuah           ###   ########.fr       */
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
 * @param main The main struct containing the environment list
 * @param key The key of the value that will be deleted
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
		split = envp_split(main->envp[i]);
		if (ft_strcmp(split[0], key) != 0)
			new_envp[j++] = ft_strdup(main->envp[i]);
		free_doublearray(split);
	}
	free_doublearray(main->envp);
	main->envp = new_envp;
}

/**
 * @brief Checks whether the arg is valid. If so then find and delete the
 * envp based on the key
 * 
 * @param main The main struct containing the environment list
 * @param args The arguments
 * @return int 0 on success
 */
int	unset(t_main *main, char **args)
{
	int		i;

	i = 0;
	while (args[++i] != 0)
	{
		if (check_valid_identifier(args[i], args[i], "unset") == 0)
			find_and_delete(main, args[i]);
		else
			return (1);
	}
	return (0);
}
