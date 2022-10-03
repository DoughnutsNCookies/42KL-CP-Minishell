/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:55:56 by schuah            #+#    #+#             */
/*   Updated: 2022/10/03 16:36:09 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get the dir object
 * 
 * @param path The path of the dir
 * @return DIR* object
 */
DIR	*get_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	free(path);
	return (dir);
}

/**
 * @brief Get the files in linked list format. Reads through every file's name
 * and checks whether it is valid according to the argument. If it is, store the
 * file's name into a linked list and returns
 * 
 * @param entity The dirent from readdir
 * @param dir The directory object
 * @param arg The argument to check if a file's name is valid
 * @param file_name The file name of the first valid file if there's one
 * @return The head of the filename's linked list.
 */
static t_list	*get_files_lst(struct dirent *entity, DIR *dir,
	char *arg, char *file_name)
{
	t_list	*current;
	t_list	*head;

	current = ft_lstnew(ft_calloc(1, sizeof(char *)));
	head = current;
	ft_memcpy(current->content, &file_name, sizeof(char *));
	entity = readdir(dir);
	while (entity != NULL)
	{
		file_name = ft_strdup(entity->d_name);
		if (is_valid(file_name, arg) == 1)
		{
			current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
			current = current->next;
			ft_memcpy(current->content, &file_name, sizeof(char *));
		}
		else
			free(file_name);
		entity = readdir(dir);
	}
	closedir(dir);
	return (head);
}

/**
 * @brief Get the files from dir object. Checks through every file's name for the
 * first node. If reached NULL and no suitable file was found, return NULL, else
 * returns the file name's linked list
 * 
 * @param arg The argument to check if a file's name is valid
 * @return The head of the filename's linked list, NULL if there's no valid files
 */
t_list	*get_files_from_dir(char *arg)
{
	DIR					*dir;
	struct dirent		*entity;
	char				*file_name;

	dir = get_dir(getcwd(NULL, 0));
	entity = readdir(dir);
	while (entity != NULL)
	{
		file_name = ft_strdup(entity->d_name);
		if (is_valid(file_name, arg) == 0)
			entity = readdir(dir);
		else
			break ;
		free(file_name);
	}
	if (entity == NULL)
	{
		closedir(dir);
		return (NULL);
	}
	return (get_files_lst(entity, dir, arg, file_name));
}
