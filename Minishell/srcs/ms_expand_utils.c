/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:03:10 by schuah            #+#    #+#             */
/*   Updated: 2022/10/06 11:27:32 by schuah           ###   ########.fr       */
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
