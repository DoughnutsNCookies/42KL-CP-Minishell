/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_debugger.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:38:51 by schuah            #+#    #+#             */
/*   Updated: 2022/10/07 12:16:29 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief To print the linked list
 * 
 * @param head The head of the linked list
 */
void	print_ll(t_list *head)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = head;
	ft_printf("\nPRINTING LL\n");
	while (temp != NULL)
	{
		ft_printf("%d: |%s|\n", i++, *(char **)temp->content);
		temp = temp->next;
	}
	ft_printf("PRINTING END\n");
}
