/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:34:27 by schuah            #+#    #+#             */
/*   Updated: 2022/09/26 19:55:09 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_dollar(t_main *main, char *arg, char **output)
{
	char	*key;
	char	*value;
	int		push;
	int		i;

	i = 1;
	while (arg[i] != '\0' && arg[i] != '\''
		&& arg[i] != '\"' && arg[i] != '$')
		i++;
	push = i;
	key = ft_calloc(i, sizeof(char));
	key[--i] = '\0';
	while (--i >= 0)
		key[i] = arg[i + 1];
	value = get_envp_value(main->envp, key);
	if (value != NULL)
		while (value[++i] != '\0')
			*output = append_char(*output, value[i]);
	return (push - 1);
}

void	convert_quote(t_main *main, char *arg, t_list *current)
{
	char	*output;
	char	**split;
	t_list	*end;
	t_list	*head;
	int		i;
	int		j;

	i = 0;
	output = NULL;
	while (*(arg + i) != '\0')
	{
		if (*(arg + i) == '\'')
		{
			while (*(arg + ++i) != '\'' && *(arg + i) != '\0')
				output = append_char(output, *(arg + i));
		}
		else if (*(arg + i) == '\"')
		{
			while (*(arg + ++i) != '\"' && *(arg + i) != '\0')
			{
				if (*(arg + i) == '$')
					i += expand_dollar(main, arg + i, &output);
				else
					output = append_char(output, *(arg + i));
			}
		}
		else if (*(arg + i) == '$')
		{
			i += expand_dollar(main, arg + i, &output);
			split = ft_split(output, ' ');
			head = current;
			end = current->next;
			free(current->content);
			j = 0;
			ft_printf("split: |%s|\n", split[j]);
			char	*temp = ft_strdup(split[j]);
			current->content = &temp;
			ft_printf("ll: |%s|\n", *(char **)current->content);
			while (split[++j] != 0)
			{
				current->next = ft_lstnew(&split[j]);
				current = current->next;
			}
			current->next = end;
			while (head != NULL)
			{
				ft_printf("in loop: |%s|\n", *(char **)head->content);
				head = head->next;
			}
			free_doublearray(split);
			ft_printf("%c", (arg + i));
			exit(1);
		}
		else
			output = append_char(output, *(arg + i));
		i++;
	}
	free(arg);
	*(char **)current->content = output;
}

char	**expander(t_main *main, char **args)
{
	t_list	*arg_lst;
	t_list	*head;
	int		i;

	i = 0;
	while (args[i] != 0)
		i++;
	arg_lst = ft_array_to_list(args, i, sizeof(char *));
	head = arg_lst;
	while (arg_lst != NULL)
	{
		convert_quote(main, *(char **)arg_lst->content, arg_lst);
		ft_printf("|%s|\n", *(char **)arg_lst->content);
		arg_lst = arg_lst->next;
	}
	exit(1);
	char **temp = ft_list_to_array(arg_lst, sizeof(char *));
	return (temp);
	(void)main;
}
