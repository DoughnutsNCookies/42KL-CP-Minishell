/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_star.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:58:57 by schuah            #+#    #+#             */
/*   Updated: 2022/10/11 13:01:07 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Loops through all * in the arg. If arg has reached '\0', return 1.
 * Checks whether the current file name character is the same as the current arg
 * character after *. If the current file name character has reached '\0' but
 * the current arg character has not, return 0. Loops until the characters don't
 * match. Recurs through is_valid function again with remaining arg, for
 * scenarios like file name is "srcs", and arg is "*s". Returns 1 if is_valid.
 * Check if arg has reached '\0' and file name has not reached '\0', means the
 * arg do not match and return (0). Else return -1 to start this loop again 
 * 
 * @param tocheck File name that will be checked
 * @param arg Argument that will be checked with
 * @param i Current position of the file name
 * @param j Current position of the argument
 * @return int 1 if the file name is valid with the *, else 0
 */
static int	check_valid_star(char **tocheck_in, char **arg_in, int *i, int *j)
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
	if (is_valid(tocheck + *i, arg + *j - 1))
		return (1);
	(*j)++;
	if (arg[*j] == '\0' && tocheck[*i] != '\0')
		return (0);
	return (-1);
}

/**
 * @brief Checks the file name after any * (eg. the s after *s) and checks
 * whether the current arg character and the current file name character is the
 * same
 * 
 * @param tocheck File name that will be checked
 * @param arg Argument that will be checked with
 * @param i Current position of the file name
 * @param j Current position of the argument
 * @return int 1 if it is the same, else 0
 */
static int	check_end_string(char *tocheck, char *arg, int *i, int *j)
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
 * @brief Checks whether the file name is valid based on the argument given.
 * 
 * @param tocheck File name that will be checked
 * @param arg Argument that will be checked with
 * @return int 1 if it is valid and is not a hidden file, else 0
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
			output = check_valid_star(&tocheck, &arg, &i, &j);
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
 * @brief Checks whether there is a * character in the argument, and whether the
 * current directory can be opened
 * 
 * @param arg Argument that will be checked
 * @return int 1 if there is a * character in the argument and the current
 * directory can be opened, else 0
 */
int	check_star(char *arg)
{
	DIR		*dir;

	if (ft_strchr(arg, '*') == NULL)
		return (0);
	dir = get_dir(getcwd(NULL, 0));
	if (dir == NULL)
		return (0);
	closedir(dir);
	return (1);
}
