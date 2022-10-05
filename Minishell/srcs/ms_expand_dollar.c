/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_dlr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:18:02 by schuah            #+#    #+#             */
/*   Updated: 2022/10/04 19:34:49 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Replace the contents of the current node with the list of files and,
 * creates new nodes for every other files
 * 
 * @param cur_in The current node of the argument linked list
 * @param split The singular argument that was split by its respective $ value
 */
void	replace_cur_with_files(t_list **cur_in, char *split)
{
	t_list	*files;
	t_list	*head;
	t_list	*current;

	current = *cur_in;
	files = get_files_from_dir(split);
	head = files;
	if (files == NULL)
		ft_memcpy(current->content, split, sizeof(char *));
	else
	{
		while (files != NULL)
		{
			ft_memcpy(current->content, files->content, sizeof(char *));
			if (files->next != NULL)
			{
				current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
				current = current->next;
			}
			files = files->next;
		}
		ft_lstclear(&head, &free);
		free(split);
	}
	*cur_in = current;
}

static t_list	*split_value_to_args(t_list **cur_in, t_expand *exp)
{
	t_list	*end;
	t_list	*current;
	char	**split;
	int		j;

	current = *cur_in;
	split = ft_split(exp->output, ' ');
	end = current->next;
	j = -1;
	while (split[++j] != 0)
	{
		ft_memcpy(current->content, split + j, sizeof(char *));
		if (split[j + 1] != 0)
		{
			current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
			current = current->next;
		}
	}
	free(split);
	*cur_in = current;
	return (end);
}

/**
 * @brief Expands $ to its respective key and replacing the current argument
 * node to the value list
 * 
 * @param cur_in The current node of the argument list
 * @param exp The expansion struct containing the argument, i position and
 * output string
 * @param dollar_expanded The value of the $
 * @return int 1 if expansion of $ is done, else 0
 */
int	expand_dlr(t_list **cur_in, t_expand *exp, char *dollar_expanded)
{
	t_list	*end;
	t_list	*current;
	int		j;

	current = *cur_in;
	if (dollar_expanded != NULL)
	{
		if (dollar_expanded[0] != '\0')
		{
			j = -1;
			while (dollar_expanded[++j] != '\0')
				exp->output = append_char(exp->output, dollar_expanded[j]);
			end = split_value_to_args(&current, exp);
			current->next = end;
			free(exp->output);
			exp->output = *(char **)current->content;
			*cur_in = current;
			free(dollar_expanded);
			return (1);
		}
	}
	*cur_in = current;
	free(dollar_expanded);
	return (0);
}
