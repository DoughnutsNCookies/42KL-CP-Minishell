/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:34:27 by schuah            #+#    #+#             */
/*   Updated: 2022/09/23 11:45:02 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_dollar(t_main *main, char *arg, int *i)
{
	char	*key;
	char	*value;
	int		temp;
	int		size;

	size = 0;
	while (arg[*i] != '\0' && arg[*i] != '\''
		&& arg[*i] != '\"' && arg[*i] != '&')
	{
		(*i)++;
		size++;
	}
	key = malloc(sizeof(char) * size);
	if (key == NULL)
		return ;
	temp = *i;
	key[--size] = '\0';
	while (arg[--temp] != '$')
		key[--size] = arg[temp];
	value = get_envp_value(main->envp, key);
	if (value != NULL)
		ft_printf("%s", value);
	else
		ft_printf("%s", key);
	(*i)--;
}

static char	**convert_quote(t_main *main, char *arg, t_list *current)
{
	int		i;

	i = -1;
	while (arg[++i] != '\0')
	{
		if (arg[i] == '\'')
		{
			while (arg[++i] != '\0' && arg[i] != '\'')
				ft_printf("%c", arg[i]);
		}
		else if (arg[i] == '\"')
		{	
			while (arg[++i] != '\0' && arg[i] != '\"')
			{
				if (arg[i] == '$')
					expand_dollar(main, arg, &i);
				else
					ft_printf("%c", arg[i]);
			}
		}
		else if (arg[i] == '$')
		{	
		}
		else
			ft_printf("%c", arg[i]);
	}
	// ft_printf("%s\n", *(char **)current->content);
	(void)main;
	return (NULL);
	(void)current;
}

char	**expander(t_main *main, char **args)
{
	char	**output;
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
		output = convert_quote(main, *(char **)arg_lst->content, arg_lst);
		arg_lst = arg_lst->next;
	}
	exit(1);
	output = ft_list_to_array(arg_lst, sizeof(char *));
	return (output);
	(void)main;
}
