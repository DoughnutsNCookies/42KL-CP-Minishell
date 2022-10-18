/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:19:28 by maliew            #+#    #+#             */
/*   Updated: 2022/10/18 11:45:52 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Deletes the node of the argument list if the content is NULL
 * 
 * @param list List of arguments to delete null from
 */
void	ms_expander_delete_null(t_list **list)
{
	t_list	*curr;

	if (list == NULL || *list == NULL)
		return ;
	curr = *list;
	if (*(char **)curr->content == NULL)
	{
		*list = curr->next;
		free(curr->content);
		free(curr);
		curr = NULL;
		ms_expander_delete_null(list);
	}
	curr = *list;
	if (curr)
		ms_expander_delete_null(&curr->next);
}

/**
 * @brief Checks if the string has spaces only
 * 
 * @param str The string to check
 * @return int 1 if the string only has spaces, else 0
 */
int	is_space_only(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	return (str[i] == '\0');
}

/**
 * @brief Checks whether the character c is one of the charset
 * 
 * @param c Character to check
 * @param charset Charset to compare with
 * @param null 1 to check for '\0', else 0
 * @param space 1 to check for ' ', else 0
 * @return int 1 if it is one of the charset, else 0
 */
int	is_charset(char c, char *charset, int null, int space)
{
	char	**split;
	int		output;
	int		i;

	if (space == 1 && c == ' ')
		return (1);
	if (null == 1 && c == '\0')
		return (1);
	split = ft_split(charset, ' ');
	output = 0;
	i = -1;
	while (split[++i] != 0)
		if (split[i][0] == c)
			output = 1;
	free_doublearray(split);
	return (output);
}