/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expandstar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:58:57 by schuah            #+#    #+#             */
/*   Updated: 2022/09/30 20:33:01 by schuah           ###   ########.fr       */
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

t_list	*get_files_from_dir(char *arg)
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
		ft_dprintf(2, "Cannot open file\n");
		return (NULL);
	}
	entity = readdir(dir);
	while (entity != NULL)
	{
		temp = ft_strdup(entity->d_name);
		if (is_valid(temp, arg) == 0)
			entity = readdir(dir);
		else
			break ;
		free(temp);
	}
	if (entity == NULL)
		return (NULL);
	current = ft_lstnew(ft_calloc(1, sizeof(char *)));
	head = current;
	ft_memcpy(current->content, &temp, sizeof(char *));
	entity = readdir(dir);
	while (entity != NULL)
	{
		temp = ft_strdup(entity->d_name);
		if (is_valid(temp, arg) == 1)
		{
			current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
			current = current->next;
			ft_memcpy(current->content, &temp, sizeof(char *));
		}
		else
			free(temp);
		entity = readdir(dir);
	}
	ft_lstsort(&head);
	closedir(dir);
	return (head);
}

int	check_star(char *arg)
{
	char	*path;
	DIR		*dir;

	if (ft_strchr(arg, '*') == NULL)
		return (0);
	path = getcwd(NULL, 0);
	dir = opendir(path);
	free(path);
	if (dir == NULL)
	{
		ft_dprintf(2, "Cannot open file\n");
		return (0);
	}
	closedir(dir);
	return (1);
}

t_list	*star_wildcard(char *arg, t_list *current)
{
	t_list	*files;
	t_list	*end;

	files = get_files_from_dir(arg);
	print_ll(files);
	end = current->next;
	current = files;
	while (current->next != NULL)
		current = current->next;
	current->next = end;
	print_ll(current);
	return (current);
}
