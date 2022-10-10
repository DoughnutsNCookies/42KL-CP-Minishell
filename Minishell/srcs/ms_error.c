/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:05:01 by schuah            #+#    #+#             */
/*   Updated: 2022/10/10 10:18:40 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints perror and exit with status 1
 * 
 * @param errormsg The error message to be printed
 */
void	perror_and_exit(char *errormsg)
{
	perror(errormsg);
	exit(EXIT_FAILURE);
}

/**
 * @brief Prints custom error message for invalid identifier for export. Updates
 * the errno to 1
 * 
 * @param arg The arguments
 * @param type The type of builtin function it is called from (unset or export)
 * @return int 1 on success
 */
int	export_unset_error(char *arg, char *type)
{
	ft_dprintf(STDERR_FILENO, "%s: `%s': not a valid identifier\n", type, arg);
	return (1);
}
