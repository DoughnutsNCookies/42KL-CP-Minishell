/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:28:28 by schuah            #+#    #+#             */
/*   Updated: 2022/09/28 11:51:49 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets and prints out the current directory of the program
 * 
 * @param main The main struct (Can be NULL)
 * @param args The arguments (Can be NULL)
 * @return int 0 on success
 */
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
