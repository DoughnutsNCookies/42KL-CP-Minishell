/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:31:25 by schuah            #+#    #+#             */
/*   Updated: 2022/09/23 10:22:27 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Frees double array (ie. output from ft_split) */
void	free_doublearray(char **split)
{
	int	i;

	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

/* Creates a duplicate of a double array */
char	**dup_doublearray(char **src)
{
	char	**output;
	int		i;

	i = 0;
	while (src[i] != 0)
		i++;
	output = ft_calloc(i + 1, sizeof(char *));
	output[i] = 0;
	while (--i >= 0)
		output[i] = ft_strdup(src[i]);
	return (output);
}

/* Gets the value from envp based on key */
char	*get_envp_value(char **envp, char *key)
{
	char	**split;
	char	*value;
	int		i;

	i = -1;
	while (envp[++i] != 0)
	{
		split = envp_split(envp[i]);
		if (ft_strcmp(split[0], key) == 0)
		{
			value = ft_strdup(split[1]);
			free_doublearray(split);
			return (value);
		}
		free_doublearray(split);
	}
	return (NULL);
}
