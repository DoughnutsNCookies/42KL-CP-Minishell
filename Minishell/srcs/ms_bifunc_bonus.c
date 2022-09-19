/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_bifunc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:01:52 by schuah            #+#    #+#             */
/*   Updated: 2022/09/19 13:50:02 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Initializes all of the functions pointers with their respective names
** Creates a copy of envp and saves it into the struct */
void	init_main(t_main *main, char **envp)
{
	main->func_name = ft_split("echo cd pwd export unset env exit", ' ');
	main->func[MS_ECHO] = echo;
	main->func[MS_CD] = cd;
	main->func[MS_PWD] = pwd;
	main->func[MS_EXPORT] = export;
	main->func[MS_UNSET] = unset;
	main->func[MS_ENV] = env;
	main->func[MS_EXIT] = ms_exit;
	main->envp = dup_doublearray(envp);
}
