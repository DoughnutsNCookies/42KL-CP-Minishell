/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:31:25 by schuah            #+#    #+#             */
/*   Updated: 2022/10/17 21:02:35 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees double array (i.e. output from ft_split)
 * 
 * @param split Double array that will be freed
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
 * @param src Double array source that will be duplicated
 * @return char** double array that was duplicated from src
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
 * @param envp Enviroment variables array to get the values from
 * @param key Key of the value
 * @return char* value of the key if the key is found, else NULL if its not found
 */
char	*get_envp_value(char **envp, char *key)
{
	char	**split;
	char	*value;
	int		i;

	i = -1;
	if (key != NULL)
		if (key[0] == '?' && key[1] == '\0')
			return (ft_itoa(g_errno));
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

/**
 * @brief Duplicates and returns a copy of envp and sorts it in alphabatical
 * order
 * 
 * @param envp The enviroment variable array
 * @return char** envp that is malloc'ed and sorted
 */
char	**sort_doublearray(char **array)
{
	int		i;
	int		j;
	int		max;
	char	**output;
	char	*temp;

	output = dup_doublearray(array);
	max = 0;
	while (array[max] != 0)
		max++;
	i = -1;
	while (++i < max)
	{
		j = i;
		while (++j < max)
		{
			if (ft_strcmp(output[i], output[j]) > 0)
			{
				temp = output[i];
				output[i] = output[j];
				output[j] = temp;
			}
		}
	}
	return (output);
}
