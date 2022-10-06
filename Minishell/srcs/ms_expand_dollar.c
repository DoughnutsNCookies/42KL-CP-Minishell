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

static t_list	*split_value(t_list **cur_in, t_expand *exp, char *d_value)
{
	t_list	*end;
	t_list	*current;
	char	**split;
	char	*temp;
	int		j;

	current = *cur_in;
	end = current->next;
	split = ft_split(d_value, ' ');
	j = 0;
	if (split[j] != 0)
	{
		if (exp->output != NULL)
			temp = ft_strjoin(exp->output, split[j]);
		else
			temp = ft_strdup(split[j]);
		ft_memcpy(current->content, &temp, sizeof(char *));
		if (split[j + 1] != 0)
		{
			current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
			current = current->next;
		}
		free(split[j]);
	}
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

int	expand_dlr(t_list **cur_in, t_expand *exp, char *d_value)
{
	t_list	*end;
	t_list	*current;

	current = *cur_in;
	if (d_value == NULL && exp->arg[exp->i] == '$' && exp->arg[exp->i + 1] == '\0')
		exp->output = append_char(exp->output, '$');
	else if (d_value != NULL)
	{
		if (d_value[0] != '\0')
		{
			end = split_value(&current, exp, d_value);
			current->next = end;
			free(exp->output);
			exp->output = *(char **)current->content;
			*cur_in = current;
			free(d_value);
			return (1);
		}
	}
	*cur_in = current;
	free(d_value);
	return (0);
}

/**
 * @brief Expands the $ symbol by finding its value. Gets the key from the arg
 * and use the key to loop through every environment variable to find a
 * matching key
 * 
 * @param main The main struct containing the environment list
 * @param arg The argument containing the key
 * @return char* value if a matching key is found, else returns NULL 
 */
char	*dlr_val(t_main *main, char *arg)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (arg[i] != '\0' && arg[i] != '\''
		&& arg[i] != '\"' && arg[i] != '$' && arg[i] != '*')
		i++;
	key = ft_calloc(i, sizeof(char));
	key[--i] = '\0';
	while (--i >= 0)
		key[i] = arg[i + 1];
	value = get_envp_value(main->envp, key);
	free(key);
	return (value);
}

void	recurs_expand_dollar(t_main *main, t_expand *exp)
{
	char	*dollar_expanded;
	int		i;

	if (exp->arg[exp->i + 1] != '$')
		return ;
	exp->i++;
	i = -1;
	dollar_expanded = dlr_val(main, exp->arg + exp->i);
	if (dollar_expanded != NULL)
		while (dollar_expanded[++i] != '\0' && dollar_expanded[0] != '\0')
			exp->output = append_char(exp->output, dollar_expanded[i]);
	while (exp->arg[exp->i + 1] != '\0' && exp->arg[exp->i + 1] != '\''
		&& exp->arg[exp->i + 1] != '\"' && exp->arg[exp->i + 1] != '$')
			exp->i++;
	free(dollar_expanded);
	recurs_expand_dollar(main, exp);
}