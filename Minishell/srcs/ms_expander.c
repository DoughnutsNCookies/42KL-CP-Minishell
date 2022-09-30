/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:34:27 by schuah            #+#    #+#             */
/*   Updated: 2022/09/30 11:58:50 by schuah           ###   ########.fr       */
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
	t_list	*end;
	t_list	*head;
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
			head = current;
			star_wildcard(arg, current);
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
				/////
				while (split[++j] != 0)
				{
					// star_wildcard(split[j], current);
					// print_ll(head);
					// exit(1);
					ft_memcpy(current->content, split + j, sizeof(char *));
					current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
					current = current->next;
				}
				/////
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
		ft_memcpy(current->content, ft_calloc(1, sizeof(char *)),
			sizeof(char *));
	}
	else if (dollar == 0)
		*(char **)current->content = output;
	return (current->next);
}

void	expander(t_main *main, t_list **args)
{
	t_list	*arg_lst;

	arg_lst = *args;
	if (arg_lst == NULL)
	{
		*args = ft_lstnew(ft_calloc(1, sizeof(char *)));
		return ;
	}
	while (arg_lst != NULL)
		arg_lst = convert_quote(main, *(char **)arg_lst->content, arg_lst);
	ft_lstadd_back(args, ft_lstnew(ft_calloc(1, sizeof(char *))));
}
