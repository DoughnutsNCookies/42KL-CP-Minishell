/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:07:12 by maliew            #+#    #+#             */
/*   Updated: 2022/09/30 02:05:27 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Inits parser struct with lexer.
 * 
 * @param lexer Lexer struct to be used by parser.
 * @return t_parser* Pointer to parser struct.
 */
t_parser	*ms_parser_init(t_lexer *lexer)
{
	t_parser	*parser;

	parser = ft_calloc(1, sizeof (t_parser));
	parser->lexer = lexer;
	parser->curr_token = ms_lexer_next(lexer);
	parser->syntax_error = 0;
	return (parser);
}

/**
 * @brief Frees current token and gets next token from lexer.\
 * @brief If current token is special, i.e. not a word token, free the value.\
 * @brief \
 * @brief nom nom yummy tokens~
 * 
 * @param parser Parser struct.
 */
void	ms_parser_eat(t_parser *parser)
{
	if (parser->curr_token->e_type != TOKEN_WORD)
		free(parser->curr_token->value);
	ms_token_free(&parser->curr_token);
	parser->curr_token = ms_lexer_next(parser->lexer);
}

/**
 * @brief Frees parser struct and sets pointer to NULL.
 * 
 * @param parser Pointer to pointer to parser struct.
 */
void	ms_parser_free(t_parser **parser)
{
	free((*parser)->curr_token->value);
	free((*parser)->curr_token);
	ms_lexer_free(&(*parser)->lexer);
	free(*parser);
	parser = NULL;
}
