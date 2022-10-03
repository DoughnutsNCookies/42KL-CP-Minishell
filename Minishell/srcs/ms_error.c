/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 21:05:01 by schuah            #+#    #+#             */
/*   Updated: 2022/09/30 02:24:03 by maliew           ###   ########.fr       */
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
	g_global.error_no = 1;
	return (1);
}

/**
 * @brief 	Prints syntax error using the current token in the parser.
 * 			Also sets the member syntax_error in the parser struct to 1.
 * 
 * @param p Parser struct
 */
void	ms_parser_syntax_error(t_parser *p)
{
	ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n",
		p->curr_token->value);
	p->syntax_error = 1;
}
