/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:15:07 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/03 00:31:37 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

bool	check_operatorsyntax(t_token *token)
{
	if (token->next->kind == TK_EOF)
	{
		tk_error_manager("Invalid syntax: operator followed by newline");
		return (false);
	}
	if (ft_strncmp(token->word, "||", 2) == 0 || \
	ft_strncmp(token->word, "&&", 2) == 0 || ft_strncmp(token->word, ";", 1))
	{
		if (token->next->kind != TK_WORD && token->next->kind != TK_OPERATOR \
		&& ft_strncmp(token->next->word, "(", 1) != 0)
		{
			tk_error_manager("Invalid syntax: operator followed by invalid token");
			return (false); 
		}
	}
	if (ft_strncmp(token->word, "|", 1) == 0)
	{
		if (token->next->kind != TK_WORD)
		{
			tk_error_manager("Invalid syntax: pipe followed by invalid token");
			return (false);
		}
	}
	if  (ft_strncmp(token->word, "(", 1) == 0)
	{
		if (token->next->word != TK_OPERATOR || ft_strncmp(token->next->word, ")", 1) != 0)
		{
			tk_error_manager("Invalid syntax: operator or closing parnthesis");
			return (false);
		}
	}
	return (true);
}

/**
 * * check_redirectsyntax
 *  checks if redirect is valid, followed by expected tokens
*/

bool	check_redirectsyntax(t_token *token)
{
	if (token->next->kind == TK_EOF)
	{
		tk_error_manager("Invalid Syntax: redirect followed by newline");
		return (false);
	}
	if (token->next->kind == TK_REDIRECT && token->word[0] \
		!= token->next->word[0])
	{
		tk_error_manager("Invalid syntax: redirect followed by invalid token");
		return (false);
	}
	if (token->kind == TK_REDIRECT && token->next->kind == TK_REDIRECT \
		&& token->next->next->kind == TK_REDIRECT)
	{
		tk_error_manager("Invalid syntax: unrecognized redirection");
		return (false);
	}
	if (token->next->kind == TK_OPERATOR)
	{
		tk_error_manager("Invalid syntax: redirect followed by operator");
		return (false);
	}
	return (true); 
}

bool	check_tokens(t_token *tokens)
{
	while (tokens != NULL)
	{
		if (tokens->kind == TK_REDIRECT)
		{
			if (check_redirectsyntax(tokens) == false)
				return (false);
		}
		if (tokens->kind == TK_OPERATOR)
		{
			if (check_operatorsyntax(tokens) == false)
				return (false);
		}
		tokens = tokens->next;
	}
	return (true);
}