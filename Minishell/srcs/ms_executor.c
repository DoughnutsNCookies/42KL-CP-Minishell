/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:33:40 by schuah            #+#    #+#             */
/*   Updated: 2022/09/27 13:54:38 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Loops through the available builtins function and find a match based on args
** If found, executes the function, else write error and set errno to 127 */
void	executor(t_main *main, char **command)
{
	int	i;

	i = -1;
	while (++i < MS_MAX_BIFUNC)
	{
		if (command[0] == 0)
			return ;
		if (ft_strcmp(command[0], main->func_name[i]) == 0)
		{
			g_global.error_no = main->func[i](main, command);
			return ;
		}
	}
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", 20);
	g_global.error_no = 127;
}
