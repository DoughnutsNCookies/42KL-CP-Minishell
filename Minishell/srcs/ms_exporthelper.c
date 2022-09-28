/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exporthelper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:49:48 by schuah            #+#    #+#             */
/*   Updated: 2022/09/28 12:18:48 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the arg is a valid candidate. If first letter is not alpha
 * or '_', print error message. If second letter and beyond is not alphanumeric
 * or '_', print error message
 * 
 * @param arg The argument
 * @param str The string that will be exported
 * @param type The type of builtin function that is called from (unset or export)
 * @return int 0 on success, else 1 if there is an error
 */
int	check_valid_identifier(char *arg, char *str, char *type)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		return (export_unset_error(arg, type));
	while (str[++i] != '\0')
		if (ft_isalnum(str[i]) == 0 && str[i] != '_' && str[i] != ' ')
			return (export_unset_error(arg, type));
	return (0);
}

/**
 * @brief Prints the sorted envp with the "declare -x" suffix and the value of
 * the variable covered with "" (eg. "value"). If key has no value, just print
 * "declare -x" with the key only
 * 
 * @param envp The enviroment variable list
 */
void	print_envp(char **envp)
{
	char	**split;
	int		i;

	i = -1;
	while (envp[++i] != 0)
	{
		split = envp_split(envp[i]);
		if (split[1] == 0)
			ft_printf("declare -x %s\n", split[0]);
		else
			ft_printf("declare -x %s=\"%s\"\n", split[0], split[1]);
		free_doublearray(split);
	}
}

/**
 * @brief Duplicates and returns a copy of envp and sorts it in alphabatical
 * order
 * 
 * @param envp The enviroment variable list
 * @return char** envp that is malloc'ed and sorted
 */
char	**sort_envp(char **envp)
{
	int		i;
	int		j;
	int		max;
	char	**output;
	char	*temp;

	output = dup_doublearray(envp);
	max = 0;
	while (envp[max] != 0)
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

/**
 * @brief Splits the str into key and value at first '=' contact.
 * 
 * @param str The string containing the key and value (eg. key=value)
 * @return char** str if str don't have =, else output[0] is key, output[1] is
 * value, output[2] is NULL terminator
 */
char	**envp_split(char *str)
{
	char	**output;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
	{
		output = malloc(sizeof(char *) * 2);
		if (output == NULL)
			return (NULL);
		output[0] = ft_strdup(str);
		output[1] = 0;
		return (output);
	}
	output = malloc(sizeof(char *) * 3);
	if (output == NULL)
		return (NULL);
	i++;
	output[0] = ft_strndup(str, i - 1);
	output[1] = ft_strndup(str + i, ft_strlen(str) - i);
	output[2] = 0;
	return (output);
}
