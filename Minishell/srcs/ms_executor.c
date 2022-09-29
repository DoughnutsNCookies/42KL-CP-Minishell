/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:33:40 by schuah            #+#    #+#             */
/*   Updated: 2022/09/29 11:30:23 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Loops through the available builtins function and find a match based
 * on args. If found, it will executes the functio. Else write error and set
 * errno to 127
 * 
 * @param main The main struct containing the builtin functions and
 * their respective names
 * @param command The command that will be executed
 */
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
	ft_dprintf(STDERR_FILENO, "%s: command not found\n", command[0]);
	g_global.error_no = 127;
}
