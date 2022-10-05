/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:03:10 by schuah            #+#    #+#             */
/*   Updated: 2022/10/05 16:54:23 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Appends a character to the back of a string and returns the malloc'ed 
 * resulting string, freeing the original one.
 * 
 * @param input The string input
 * @param c The character to be appended to the back of a string
 * @return char* The result string after appending
 */
char	*append_char(char *input, char c)
{
	char	*output;
	int		size;
	int		i;

	size = 0;
	i = 0;
	if (input != NULL)
		size = ft_strlen(input);
	output = ft_calloc(size + 2, sizeof(char));
	if (input != NULL)
	{
		while (input[i] != '\0')
		{
			output[i] = input[i];
			i++;
		}
	}
	output[i] = c;
	output[i + 1] = '\0';
	free(input);
	return (output);
}

/**
 * @brief Expands the $ symbol by finding its value. Gets the key from the arg
 * and use the key to loop through every envp to find a matching key
 * 
 * @param main The main struct containing the environment list
 * @param arg The argument containing the key
 * @return char* value if a matching key is found, else returns NULL 
 */
char	*dlr_val(t_main *main, char *arg)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (arg[i] != '\0' && arg[i] != '\''
		&& arg[i] != '\"' && arg[i] != '$' && arg[i] != '*')
		i++;
	key = ft_calloc(i, sizeof(char));
	key[--i] = '\0';
	while (--i >= 0)
		key[i] = arg[i + 1];
	value = get_envp_value(main->envp, key);
	free(key);
	return (value);
}
