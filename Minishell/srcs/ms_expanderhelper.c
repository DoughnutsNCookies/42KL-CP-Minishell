/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expanderhelper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 12:28:37 by schuah            #+#    #+#             */
/*   Updated: 2022/09/29 11:34:56 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *input, char c)
{
	char	*output;
	int		size;
	int		i;

	size = 0;
	i = 0;
	if (input != NULL)
		size = ft_strlen(input);
	output = ft_calloc(size + 2, sizeof(char));
	if (input != NULL)
	{
		while (input[i] != '\0')
		{
			output[i] = input[i];
			i++;
		}
	}
	output[i] = c;
	output[i + 1] = '\0';
	free(input);
	return (output);
}

void	print_ll(t_list *head)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = head;
	ft_printf("\nPRINTING\n");
	while (temp != NULL)
	{
		ft_printf("%d: |%s|\n", i++, *(char **)temp->content);
		temp = temp->next;
	}
	ft_printf("PRINTING END\n");
}

char	**ft_list_to_charss(t_list *lst)
{
	char	**output;
	int		i;

	output = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	i = 0;
	while (lst != NULL)
	{
		output[i++] = *(char **)lst->content;
		lst = lst->next;
	}
	output[i] = 0;
	return (output);
}