/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:53:46 by maliew            #+#    #+#             */
/*   Updated: 2022/09/30 02:17:33 by maliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Inits lexer struct with the string to parse.
 * 
 * @param input String to parse
 * @return t_lexer* Lexer struct
 */
t_lexer	*ms_lexer_init(char *input)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->input = input;
	lexer->len = ft_strlen(input);
	lexer->c = lexer->input;
	return (lexer);
}

/**
 * @brief Returns the word token from current position.
	If lexer hits a single quote (') or a double quote ("), the entire string in
	the quotes will be included, including whitespace.\
	@brief i.e. ec"ho hi" will be one token
 * 
 * @param lexer Lexer struct
 * @return t_token* Token containing a string
 */
t_token	*ms_lexer_get_word_token(t_lexer *lexer)
{
	t_token	*token;
	char	temp_quote;
	int		i;

	i = 0;
	while (!ft_isspace(*(lexer->c + i)) && *(lexer->c + i) != '\0'
		&& !ms_lexer_is_spec((lexer->c + i)))
	{
		if (*(lexer->c + i) == '\'' || *(lexer->c + i) == '"')
		{
			temp_quote = *(lexer->c + i);
			i++;
			while (*(lexer->c + i) != temp_quote && *(lexer->c + i) != '\0')
				i++;
		}
		i++;
	}
	token = ms_token_init(TOKEN_WORD, ft_substr(lexer->c, 0, i));
	lexer->c += i;
	return (token);
}

/**
 * @brief Returns the special token from the current position.
 * 
 * @param lexer Lexer struct
 * @return t_token* Special token
 */
t_token	*ms_lexer_get_spec_token(t_lexer *lexer)
{
	t_token	*token;
	char	**token_list;
	int		i;

	token_list = ft_split("&& || << >> < > | ( )", ' ');
	i = 0;
	while (i < 9
		&& ft_strncmp(lexer->c, token_list[i], ft_strlen(token_list[i])))
		i++;
	token = ms_token_init(i + 1, ft_strdup(token_list[i]));
	lexer->c += ft_strlen(token_list[i]);
	free_doublearray(token_list);
	return (token);
}

/**
 * @brief Returns the next token from the current position.
 * 
 * @param lexer Lexer struct
 * @return t_token* Next token from the lexer
 */
t_token	*ms_lexer_next(t_lexer *lexer)
{
	while (ft_isspace(*lexer->c))
		lexer->c++;
	if (*lexer->c == '\0')
		return (ms_token_init(TOKEN_NL, ft_strdup("newline")));
	else if (ms_lexer_is_spec(lexer->c))
		return (ms_lexer_get_spec_token(lexer));
	else
		return (ms_lexer_get_word_token(lexer));
}

/**
 * @brief Frees lexer struct and sets pointer to NULL.
 * 
 * @param lexer Pointer to pointer to lexer struct.
 */
void	ms_lexer_free(t_lexer **lexer)
{
	free((*lexer)->input);
	free(*lexer);
	lexer = NULL;
}
