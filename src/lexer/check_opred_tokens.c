/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opred_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:15:07 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/29 20:56:38 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

static bool	check_operatorsyntax_cont(t_token* token)
{
	if (ft_strncmp(token->word, "(", 1) == 0)
	{
		if (token->next->kind != TK_OPERATOR \
			|| ft_strncmp(token->next->word, ")", 1) != 0)
		{
			tk_error("syntax error near unexpected token ", token->next->word);
			return (false);
		}
	}
	return (true);
}

static bool	check_operatorsyntax(t_token* token)
{
	if (token->next->kind == TK_EOF)
	{
		tk_error("syntax error near unexpected token 'newline'", NULL);
		return (false);
	}
	if (ft_strncmp(token->word, "||", 2) == 0 || \
		ft_strncmp(token->word, "&&", 2) == 0 || \
		ft_strncmp(token->word, ";", 1))
	{
		if (token->next->kind != TK_WORD && token->next->kind != TK_OPERATOR \
			&& ft_strncmp(token->next->word, "(", 1) != 0)
		{
			tk_error("syntax error near unexpected token ", token->word);
			return (false);
		}
	}
	if (ft_strncmp(token->word, "|", 1) == 0)
	{
		if (token->next->kind != TK_WORD)
		{
			tk_error("syntax error near unexpected token ", token->next->word);
			return (false);
		}
	}
	return (check_operatorsyntax_cont(token));
}

/**
 * * check_redirectsyntax
 *  checks if redirect is valid, followed by expected tokens
*/
static bool	check_redirectsyntax(t_token* token)
{
	if (token->next->kind == TK_EOF)
	{
		tk_error("syntax error near unexpected token ", "'newline'");
		return (false);
	}
	if ((token->next->kind == TK_REDIRECT && token->next->next->word == NULL) \
		|| token->next->kind == TK_PIPE)
	{
		tk_error("syntax erorr near unexpected token ", token->next->word);
		return (false);
	}
	if (token->kind == TK_REDIRECT && token->next->kind == TK_REDIRECT \
		&& token->next->next->kind == TK_REDIRECT)
	{
		tk_error("syntax error near unexpected token ", token->next->word);
		return (false);
	}
	if (token->next->kind == TK_OPERATOR)
	{
		tk_error("syntax error near unexpected token ", token->next->word);
		return (false);
	}
	return (true);
}

bool	check_tokens(t_token* tokens)
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
