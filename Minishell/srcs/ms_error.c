/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:05:01 by schuah            #+#    #+#             */
/*   Updated: 2022/09/21 17:51:16 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints perror and exit with status 1 */
void	perror_and_exit(char *errormsg)
{
	perror(errormsg);
	exit(EXIT_FAILURE);
}

/* Prints custom error message for invalid identifier for export */
int	export_unset_error(char *arg, char *type)
{
	write(2, type, ft_strlen(type));
	write(2, ": `", 3);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	g_global.error_no = 1;
	return (1);
}
