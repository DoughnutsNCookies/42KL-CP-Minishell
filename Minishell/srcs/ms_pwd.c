/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:28:28 by schuah            #+#    #+#             */
/*   Updated: 2022/09/15 18:09:53 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Gets and prints out the current directory of the program */
int	pwd(t_main *main, char **args)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_printf("%s\n", path);
	free(path);
	return (0);
	(void)args;
	(void)main;
}
