/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:31:25 by schuah            #+#    #+#             */
/*   Updated: 2022/09/28 11:57:54 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees double array (ie. output from ft_split)
 * 
 * @param split The double array that will be freed
 */
void	free_doublearray(char **split)
{
	int	i;

	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
}

/**
 * @brief Creates a duplicate of a double array
 * 
 * @param src The double array source that will be duplicated
 * @return char** double array that is duplicated from src
 */
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

/**
 * @brief Gets the value from envp based on key
 * 
 * @param envp The enviroment variables to get the values from
 * @param key The key of the value
 * @return char* value if the key is found, NULL if its not found
 */
char	*get_envp_value(char **envp, char *key)
{
	char	**split;
	char	*value;
	int		i;

	i = -1;
	if (key != NULL)
		if (key[0] == '?' && key[1] == '\0')
			return (ft_itoa(g_global.error_no));
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
