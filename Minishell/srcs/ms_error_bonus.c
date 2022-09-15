/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:05:01 by schuah            #+#    #+#             */
/*   Updated: 2022/09/15 11:46:49 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Prints perror and exit with status 1 */
void	perror_and_exit(char *errormsg)
{
	perror(errormsg);
	exit(EXIT_FAILURE);
}
