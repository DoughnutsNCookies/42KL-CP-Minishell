/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:05:01 by schuah            #+#    #+#             */
/*   Updated: 2022/10/31 15:56:56 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints perror and exit with status 1
 * 
 * @param errormsg Error message to be printed
 */
void	ms_perror_and_exit(char *errormsg)
{
	perror(errormsg);
	exit(EXIT_FAILURE);
}

/**
 * @brief Prints error message for invalid identifier for export or unset and
 * updates the errno to 1
 * 
 * @param arg Argument that is invalid
 * @param type The type of builtin function it is called from (unset or export)
 * @return int 1 to be set as errno
 */
int	ms_export_unset_error(char *arg, char *type)
{
	ft_dprintf(STDERR_FILENO, "%s: `%s': not a valid identifier\n", type, arg);
	return (1);
}

/**
 * @brief Prints syntax error using the current token in the parser and sets the
 * member syntax_error in the parser struct to 1.
 * 
 * @param p Parser struct containing current token value and syntax error boolean
 */
void	ms_parser_syntax_error(t_parser *p)
{
	ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n",
		p->curr_token->value);
	p->syntax_error = 1;
}
