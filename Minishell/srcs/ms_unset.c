/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:31:05 by schuah            #+#    #+#             */
/*   Updated: 2022/09/21 20:39:09 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_and_delete(t_main *main, char *key, char *arg)
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
		if (ft_strcmp(split[0], key) == 0)
			continue ;
		new_envp[j++] = ft_strdup(main->envp[i]);
	}
	free_doublearray(main->envp);
	main->envp = new_envp;
	return ;
	(void)arg;
}

int	unset(t_main *main, char **args)
{
	int		i;

	i = 0;
	while (args[++i] != 0)
		if (check_valid_identifier(args[i], args[i], "unset") == 0)
			find_and_delete(main, args[i], args[i]);
	return (0);
}
