/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:34:27 by schuah            #+#    #+#             */
/*   Updated: 2022/09/23 15:23:39 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar(t_main *main, char *arg)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '\''
		&& arg[i] != '\"' && arg[i] != '$')
		i++;
	key = ft_calloc(i, sizeof(char));
	key[--i] = '\0';
	while (arg[--i] != '$')
		key[i] = arg[i];
	value = get_envp_value(main->envp, key);
	return (value);
}

char	*convert_quote(t_main *main, char *arg, t_list *current)
{
	int	i;

	i = -1;
	while (arg[++i] != '\0')
	{
		
	}
}

char	**expander(t_main *main, char **args)
{
	char	*output;
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
		ft_printf("%s\n", output);
		arg_lst = arg_lst->next;
	}
	exit(1);
	char **temp = ft_list_to_array(arg_lst, sizeof(char *));
	return (temp);
	(void)main;
}

// static char	*convert_quote(t_main *main, char *arg, t_list *current)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	*dollar;
// 	char	*output;

// 	i = -1;
// 	j = 0;
// 	output = ft_calloc(10000, sizeof(char));
// 	while (arg[++i] != '\0')
// 	{
// 		if (arg[i] == '\'')
// 		{
// 			while (arg[++i] != '\0' && arg[i] != '\'')
// 				output[j++] = arg[i];
// 		}
// 		else if (arg[i] == '\"')
// 		{	
// 			while (arg[++i] != '\0' && arg[i] != '\"')
// 			{
// 				if (arg[i] == '$')
// 				{
// 					dollar = expand_dollar(main, arg, &i);
// 					k = -1;
// 					while (dollar[++k] != '\0')
// 						output[j++] = dollar[k];
// 				}
// 				else
// 					output[j++] = arg[i];
// 			}
// 		}
// 		else if (arg[i] == '$')
// 		{
// 			// Need to read arg by arg for $
// 			// If got $ and is not in "", need to merge with prev words into one arg,
// 			// Any following 'args' are treated as new args, following the 'one arg'
// 		}
// 		else
// 			output[j++] = arg[i];
// 	}
// 	return (output);
// 	(void)current;
// }