/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:34:27 by schuah            #+#    #+#             */
/*   Updated: 2022/10/01 17:25:13 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar(t_main *main, char *arg)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (arg[i] != '\0' && arg[i] != '\''
		&& arg[i] != '\"' && arg[i] != '$')
		i++;
	key = ft_calloc(i, sizeof(char));
	key[--i] = '\0';
	while (--i >= 0)
		key[i] = arg[i + 1];
	value = get_envp_value(main->envp, key);
	free(key);
	return (value);
}

t_list	*convert_quote(t_main *main, char *arg, t_list *current)
{
	char	*output;
	char	*dollar_expanded;
	char	**split;
	t_list	*files;
	t_list	*end;
	int		i;
	int		j;
	int		dollar;

	i = 0;
	output = NULL;
	while (*(arg + i) != '\0')
	{
		dollar = 0;
		if (*(arg + i) == '*')
		{
			if (check_star(arg))
			{
				files = get_files_from_dir(arg);
				if (files == NULL)
					output = append_char(output, *(arg + i));
				else
				{
					end = current->next;
					ft_lstlast(files)->next = current->next;
					current->content = files->content;
					current->next = files->next;
					return (end);
				}
			}
			else
				output = append_char(output, *(arg + i));
		}
		else if (*(arg + i) == '\'')
			while (*(arg + ++i) != '\'' && *(arg + i) != '\0')
				output = append_char(output, *(arg + i));
		else if (*(arg + i) == '\"')
		{
			output = append_char(output, '\0');
			while (*(arg + ++i) != '\"' && *(arg + i) != '\0')
			{
				if (*(arg + i) == '$')
				{
					dollar_expanded = expand_dollar(main, arg + i);
					j = -1;
					if (dollar_expanded != NULL)
					{
						while (dollar_expanded[++j] != '\0')
							output = append_char(output, dollar_expanded[j]);
					}
					while (arg[i + 1] != '\0' && arg[i + 1] != '\''
						&& arg[i + 1] != '\"' && arg[i + 1] != '$')
						i++;
					free(dollar_expanded);
				}
				else
					output = append_char(output, *(arg + i));
			}
		}
		else if (*(arg + i) == '$')
		{
			dollar_expanded = expand_dollar(main, arg + i);
			while (arg[i + 1] != '\0' && arg[i + 1] != '\''
				&& arg[i + 1] != '\"' && arg[i + 1] != '$')
				i++;
			if (dollar_expanded != NULL)
			{
				j = -1;
				while (dollar_expanded[++j] != '\0')
					output = append_char(output, dollar_expanded[j]);
				split = ft_split(output, ' ');
				end = current->next;
				j = -1;
				while (split[++j] != 0)
				{
					if (check_star(split[j]))
					{
						files = get_files_from_dir(split[j]);
						if (files == NULL)
							ft_memcpy(current->content, split + j, sizeof(char *));
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
					}
					else
						ft_memcpy(current->content, split + j, sizeof(char *));
					if (split[j + 1] != 0)
					{
						current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
						current = current->next;
					}
				}
				current->next = end;
				dollar = 1;
				free(output);
				output = *(char **)current->content;
				free(split);
			}
			free(dollar_expanded);
		}
		else
			output = append_char(output, *(arg + i));
		i++;
	}
	if (output == NULL)
	{
		free(current->content);
		current->content = ft_calloc(1, sizeof(char *));
		*(char **)current->content = NULL;
	}
	else if (dollar == 0)
		*(char **)current->content = output;
	return (current->next);
	(void)main;
}

void	expander(t_main *main, t_list **args)
{
	t_list	*arg_lst;

	arg_lst = *args;
	if (arg_lst == NULL)
		return ;
	while (arg_lst != NULL)
		arg_lst = convert_quote(main, *(char **)arg_lst->content, arg_lst);
}

// t_list	*ft_lstcopy(t_list *list);

// char	*expand_dollar(t_main *main, char *arg)
// {
// 	char	*key;
// 	char	*value;
// 	int		i;

// 	i = 1;
// 	while (arg[i] != '\0' && arg[i] != '\''
// 		&& arg[i] != '\"' && arg[i] != '$')
// 		i++;
// 	key = ft_calloc(i, sizeof(char));
// 	key[--i] = '\0';
// 	while (--i >= 0)
// 		key[i] = arg[i + 1];
// 	value = get_envp_value(main->envp, key);
// 	free(key);
// 	return (value);
// }

// t_list	*convert_quote(t_main *main, char *arg, t_list *current, t_list **temp)
// {
// 	char	*output;
// 	char	*dollar_expanded;
// 	char	**split;
// 	t_list	*end;
// 	t_list	*files;
// 	int		i;
// 	int		j;
// 	int		dollar;
// 	int		k;

// 	i = 0;
// 	output = NULL;
// 	// (void)temp;
// 	while (*(arg + i) != '\0')
// 	{
// 		dollar = 0;
// 		if (*(arg + i) == '*')
// 		{
// 			output = append_char(output, '\0');
// 			if (check_star(arg) == 1)
// 			{
// 				files = get_files_from_dir(arg);
// 				// ft_printf("\nFILES: ");
// 				// print_ll(files);
// 				end = current->next;
// 				// ft_printf("\nEND: ");
// 				// print_ll(end);
// 				current = *temp;
// 				// ft_printf("\nCUR: ");
// 				// print_ll(current);
// 				*temp = files;
// 				k = -1;
// 				while (current != NULL && current->next != NULL)
// 				{// Tem
// 						break ;
// 					}
// 					current = current->next;
// 				}
// 				// current->next = end;
// 				ft_lstadd_front(temp, current);
// 				while (--k >= 0)
// 					ft_lstadd_back(temp, ft_lstcopy(files));
// 				ft_lstadd_back(temp, end);
// 				// ft_printf("\nCUR: ");
// 				// print_ll(current);
// 				// ft_printf("\nALL: ");
// 				// head = current;
// 				// print_ll(*temp);
// 				// exit(1);
// 				// current = star_wildcard(arg, current);
// 				// print_ll(current);
// 				return ((current)->next);
// 			}
// 			else
// 				output = append_char(output, *(arg + i));
// 		}
// 		else if (*(arg + i) == '\'')
// 			while (*(arg + ++i) != '\'' && *(arg + i) != '\0')
// 				output = append_char(output, *(arg + i));
// 		else if (*(arg + i) == '\"')
// 		{
// 			output = append_char(output, '\0');
// 			while (*(arg + ++i) != '\"' && *(arg + i) != '\0')
// 			{
// 				if (*(arg + i) == '$')
// 				{
// 					dollar_expanded = expand_dollar(main, arg + i);
// 					j = -1;
// 					if (dollar_expanded != NULL)
// 					{
// 						while (dollar_expanded[++j] != '\0')
// 							output = append_char(output, dollar_expanded[j]);
// 					}
// 					while (arg[i + 1] != '\0' && arg[i + 1] != '\''
// 						&& arg[i + 1] != '\"' && arg[i + 1] != '$')
// 						i++;
// 					free(dollar_expanded);
// 				}
// 				else
// 					output = append_char(output, *(arg + i));
// 			}
// 		}
// 		else if (*(arg + i) == '$')
// 		{
// 			dollar_expanded = expand_dollar(main, arg + i);
// 			while (arg[i + 1] != '\0' && arg[i + 1] != '\''
// 				&& arg[i + 1] != '\"' && arg[i + 1] != '$')
// 				i++;
// 			if (dollar_expanded != NULL)
// 			{
// 				j = -1;
// 				while (dollar_expanded[++j] != '\0')
// 					output = append_char(output, dollar_expanded[j]);
// 				split = ft_split(output, ' ');
// 				end = current->next;
// 				j = -1;
// 				/////
// 				while (split[++j] != 0)
// 				{
// 					// star_wildcard(split[j], current);
// 					// print_ll(head);
// 					// exit(1);
// 					ft_memcpy(current->content, split + j, sizeof(char *));
// 					current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
// 					current = current->next;
// 				}
// 				/////
// 				current->next = end;
// 				dollar = 1;
// 				free(output);
// 				output = *(char **)current->content;
// 				free(split);
// 			}
// 			free(dollar_expanded);
// 		}
// 		else
// 			output = append_char(output, *(arg + i));
// 		i++;
// 	}
// 	if (output == NULL)
// 	{
// 		free((current)->content);
// 		ft_memcpy((current)->content, ft_calloc(1, sizeof(char *)),
// 			sizeof(char *));
// 	}
// 	else if (dollar == 0)
// 		*(char **)(current)->content = output;
// 	return ((current)->next);
// }

// t_list	*ft_lstcopy(t_list *list)
// {
// 	t_list	*new_list;
// 	t_list	*temp;
// 	int		first;

// 	if (list == NULL)
// 		return (NULL);
// 	new_list = NULL;
// 	temp = new_list;
// 	first = 1;
// 	while (list != NULL)
// 	{
// 		if (first)
// 		{
// 			new_list = ft_lstnew(list->content);
// 			list = list->next;
// 			temp = new_list;
// 			first = 0;
// 		}
// 		if (list != NULL)
// 		{
// 			temp->next = ft_lstnew(list->content);
// 			temp = temp->next;
// 			list = list->next;
// 		}
// 	}
// 	return (new_list);
// }

// void	expander(t_main *main, t_list **args)
// {
// 	t_list	*head;
// 	t_list	*arg_lst;

// 	arg_lst = ft_lstcopy(*args);
// 	print_ll(arg_lst);
// 	head = arg_lst;
// 	// ft_printf("%p\n", *arg_lst);
// 	if (arg_lst == NULL)
// 	{
// 		*args = ft_lstnew(ft_calloc(1, sizeof(char *)));
// 		return ;
// 	}
// 	while (arg_lst->next != NULL)
// 	{
// 		// ft_printf("%s\n", *(char **)(arg_lst)->content);
// 		arg_lst = convert_quote(main, *(char **)(arg_lst)->content, arg_lst, args);
// 	}
// 	ft_lstadd_back(args, ft_lstnew(ft_calloc(1, sizeof(char *))));
// 	// ft_printf("\nEND");
// 	// ft_printf("%p\n", head);
// 	// print_ll(*head);
// }
