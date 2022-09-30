/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expandstar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:58:57 by schuah            #+#    #+#             */
/*   Updated: 2022/09/30 10:45:17 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(char *tocheck, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (tocheck[i] == '.')
		return (0);
	while (tocheck[i] != '\0' && arg[j] != '\0')
	{
		if (arg[j] == '*')
		{
			while (arg[j] == '*' && arg[j] != '\0')
				j++;
			if (arg[j] == '\0')
				return (1);
			while (tocheck[i] != '\0' && tocheck[i] != arg[j])
				i++;
			if (tocheck[i] == '\0' && arg[j] != '\0')
				return (0);
			while (tocheck[i] == arg[j])
				i++;
			j++;
			if (arg[j] == '\0' && tocheck[i] != '\0')
				return (0);
			continue ;
		}
		if (arg[j] == tocheck[i])
		{
			i++;
			j++;
		}
		else
			return (0);
		if (arg[j] == '\0' && tocheck[i] != '\0')
			return (0);
	}
	while (arg[j] == '*' && arg[j] != '\0')
		j++;
	if (tocheck[i] == '\0' && arg[j] != '\0')
		return (0);
	return (1);
}

t_list	*get_files_from_dir(void)
{
	DIR				*dir;
	struct dirent	*entity;
	t_list			*head;
	t_list			*current;
	char			*temp;
	char			*path;

	path = getcwd(NULL, 0);
	dir = opendir(path);
	free(path);
	if (dir == NULL)
	{
		printf("Canno open file\n");
		return (0);
	}
	entity = readdir(dir);
	current = ft_lstnew(ft_calloc(1, sizeof(char *)));
	temp = ft_strdup(entity->d_name);
	ft_memcpy(current->content, &temp, sizeof(char *));
	head = current;
	entity = readdir(dir);
	while (entity != NULL)
	{
		current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
		temp = ft_strdup(entity->d_name);
		current = current->next;
		ft_memcpy(current->content, &temp, sizeof(char *));
		entity = readdir(dir);
	}
	return (head);
}

void	star_wildcard(char *arg, t_list *current)
{
	t_list	*files;

	ft_printf("T");
	if (ft_strchr(arg, '*') == NULL)
		return ;
	files = get_files_from_dir();
	if (files == 0)
		return ;
	print_ll(files);
	return ;
	(void)current;
}
