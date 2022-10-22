/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:15:36 by schuah            #+#    #+#             */
/*   Updated: 2022/10/18 11:42:44 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Merges the current output with split[0] of the $ value, this is to
 * prevent splitting the existing output that have existing spacees and making
 * it into individual arguments instead of a whole. For example if existing
 * output is "echo hello $B" and $B is "hi bye world", this function will
 * transform them to "echo hello hi", "bye", "world"
 * 
 * @param cur_in Current node of the argument linked list
 * @param exp Expansion struct containing the argument, i position and
 * output string
 * @param split Splitted $ value
 */
static void	merge_first_split(t_list **cur_in, t_expand *exp, char **split)
{
	char	*temp;
	t_list	*current;

	current = *cur_in;
	if (split[0] != 0)
	{
		if (exp->output != NULL)
			temp = ft_strjoin(exp->output, split[0]);
		else
			temp = ft_strdup(split[0]);
		ft_memcpy(current->content, &temp, sizeof(char *));
		if (split[1] != 0)
		{
			current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
			current = current->next;
		}
		free(split[0]);
	}
	*cur_in = current;
}

/**
 * @brief Checks if the first split is NULL, if it is not, return 0. Else the
 * d_value is appended to the current output and is put into the current node's
 * content
 * 
 * @param cur_in Current node of the argument linked list
 * @param exp Expansion struct containing the argument, i position and output
 * string
 * @param d_value Value of $ expanded
 * @return int 0 if split[0] is not NULL, else 1
 */
static int	split_null(t_list **cur_in, t_expand *exp, char *str, char *d_value)
{
	t_list	*current;
	int		i;
	char	*temp;
	char	*temp2;

	if (str != 0)
		return (0);
	current = *cur_in;
	i = 0;
	while (d_value[i] != '\0')
		exp->output = append_char(exp->output, d_value[i++]);
	temp = ft_strdup(exp->output);
	temp2 = temp;
	temp = ft_strtrim(exp->output, " ");
	free(temp2);
	ft_memcpy(current->content, &temp, sizeof(char *));
	*cur_in = current;
	return (1);
}

/**
 * @brief Splits the $ value and assign them each a new node, linked to the
 * current node of the argument list
 * 
 * @param cur_in Current node of the argument linked list
 * @param exp Expansion struct containing the argument, i position and output
 * string
 * @param d_value Value of $ expanded
 * @return t_list* Next node of the argument linked list
 */
static t_list	*split_value(t_list **cur_in, t_expand *exp, char *d_value)
{
	t_list	*end;
	t_list	*current;
	char	**split;
	int		j;

	current = *cur_in;
	end = current->next;
	split = ft_split(d_value, ' ');
	j = 0;
	merge_first_split(&current, exp, split);
	if (split_null(&current, exp, split[0], d_value) == 0)
	{
		while (split[++j] != 0)
		{
			ft_memcpy(current->content, split + j, sizeof(char *));
			if (split[j + 1] != 0)
			{
				current->next = ft_lstnew(ft_calloc(1, sizeof(char *)));
				current = current->next;
			}
		}
	}
	free(split);
	*cur_in = current;
	return (end);
}

/**
 * @brief Expands $ to its value. If it is a single $, append '$' to the current
 * output instead. Else if the character before $ is =, get the value of $ and
 * append them to the current output, else if it is not NULL and the content are
 * not spaces only, split them into individual linked list (e.g. B="echo hi") and
 * link them to the current node of the linked list argument
 * 
 * @param cur_in Current node of the argument linked list
 * @param exp Expansion struct containing the argument, i position and
 * output string
 * @param d_value Value of $ expanded
 * @return int 1 if a conversion of $ had taken place, else 0
 */
int	expand_dlr(t_list **cur_in, t_expand *exp, char *d_value)
{
	t_list	*end;
	t_list	*current;

	current = *cur_in;
	if (d_value == NULL && exp->arg[exp->i] == '$'
		&& (exp->arg[exp->i + 1] == '\0' && val_in_quote(exp) == 0))
		exp->output = append_char(exp->output, '$');
	else if (d_value != NULL)
	{
		if (exp->i != 0 && exp->arg[exp->i - 1] == '=')
			return (strjoin_n_return(exp, d_value));
		if (d_value[0] != '\0' && is_space_only(d_value) == 0)
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
 * @brief Expands $ to its value and strjoins them to the back of the current
 * output recursively, to handle cases like "$A$B$C". The depth of the recursion
 * is stored for debugging use and to also reduce exp->i by one at the start of
 * this recursion, as well as to append '' to the starting string
 * 
 * @param main Main struct containing the environement array
 * @param exp Expansion struct containing the argument, i position and
 * output string
 * @param depth Depth of the recursion
 */
void	recurs_expand_dollar(t_main *main, t_expand *exp, int depth)
{
	char	*dollar_expanded;
	int		i;

	if (depth == 0)
		exp->i--;
	if (exp->arg[exp->i + 1] != '$')
		return ;
	if (depth == 0)
		exp->output = append_char(exp->output, '\'');
	exp->i++;
	i = -1;
	dollar_expanded = dlr_val(main, exp->arg + exp->i);
	if (dollar_expanded != NULL)
		while (dollar_expanded[++i] != '\0' && dollar_expanded[0] != '\0')
			exp->output = append_char(exp->output, dollar_expanded[i]);
	while (ft_isalnum(exp->arg[exp->i + 1]) || exp->arg[exp->i + 1] == '?')
		exp->i++;
	free(dollar_expanded);
	recurs_expand_dollar(main, exp, depth + 1);
	if (depth == 0)
		exp->output = append_char(exp->output, '\'');
}
