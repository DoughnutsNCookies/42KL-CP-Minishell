/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_star.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:58:57 by schuah            #+#    #+#             */
/*   Updated: 2022/10/04 12:47:10 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks whether the file's name will reach null after *
 * 
 * @param tocheck The file's name that will be checked
 * @param arg The argument that will be checked with
 * @param i The current position of the file's name
 * @param j The current position of the argument
 * @return int 1 if the file's name is valid with the *, else 0
 */
int	check_star_is_valid(char **tocheck_in, char **arg_in, int *i, int *j)
{
	char	*tocheck;
	char	*arg;

	tocheck = *tocheck_in;
	arg = *arg_in;
	while (arg[*j] == '*' && arg[*j] != '\0')
		(*j)++;
	if (arg[*j] == '\0')
		return (1);
	while (tocheck[*i] != '\0' && tocheck[*i] != arg[*j])
		(*i)++;
	if (tocheck[*i] == '\0' && arg[*j] != '\0')
		return (0);
	while (tocheck[*i] == arg[*j])
		(*i)++;
	if (is_valid(tocheck + *i, arg))
		return (1);
	(*j)++;
	if (arg[*j] == '\0' && tocheck[*i] != '\0')
		return (0);
	return (-1);
}

/**
 * @brief Checks the file's name after any * (eg. the s after *s)
 * 
 * @param tocheck The file's name that will be checked
 * @param arg The argument that will be checked with
 * @param i The current position of the file's name
 * @param j The current position of the argument
 * @return int 1 if it is the same, else 0
 */
int	check_end_string(char *tocheck, char *arg, int *i, int *j)
{
	if (arg[*j] == tocheck[*i])
	{
		(*i)++;
		(*j)++;
	}
	else
		return (0);
	return (arg[*j] != '\0' || tocheck[*i] == '\0');
}

/**
 * @brief Checks whether the file's name is valid based on the argument given
 * 
 * @param tocheck The file's name that will be checked
 * @param arg The argument that will be checked with
 * @return int 1 if it is valid, else 0
 */
int	is_valid(char *tocheck, char *arg)
{
	int	i;
	int	j;
	int	output;

	i = 0;
	j = 0;
	if (tocheck[i] == '.')
		return (0);
	while (tocheck[i] != '\0' && arg[j] != '\0')
	{
		if (arg[j] == '*')
		{
			output = check_star_is_valid(&tocheck, &arg, &i, &j);
			if (output >= 0)
				return (output);
			continue ;
		}
		if (check_end_string(tocheck, arg, &i, &j) == 0)
			return (0);
	}
	while (arg[j] == '*' && arg[j] != '\0')
		j++;
	if (tocheck[i] == '\0' && arg[j] != '\0')
		return (0);
	return (1);
}

/**
 * @brief Checks whether there is a star in the directory, and whether the
 * directory can be opened
 * 
 * @param arg 
 * @return int 
 */
int	check_star(char *arg)
{
	DIR		*dir;

	if (ft_strchr(arg, '*') == NULL)
		return (0);
	dir = get_dir(getcwd(NULL, 0));
	if (dir == NULL)
	{
		ft_dprintf(2, "Cannot open directory\n");
		return (0);
	}
	closedir(dir);
	return (1);
}