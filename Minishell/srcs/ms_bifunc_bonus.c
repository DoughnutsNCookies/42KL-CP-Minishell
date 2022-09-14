/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_bifunc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:01:52 by schuah            #+#    #+#             */
/*   Updated: 2022/09/14 20:31:04 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_main(t_main *main, char **envp)
{
	int	i;

	main->func_name = ft_split("echo cd pwd export unset env exit", ' ');
	main->func[0] = echo;
	main->func[1] = cd;
	main->func[2] = pwd;
	main->func[3] = export;
	main->func[4] = unset;
	main->func[5] = env;
	main->func[6] = ms_exit;
	i = 0;
	while (envp[i] != 0)
		i++;
	main->envp = ft_calloc(i + 1, sizeof(char *));
	main->envp[i] = 0;
	while (--i >= 0)
		main->envp[i] = ft_strdup(envp[i]);
}
