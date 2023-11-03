/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:12:54 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/04 00:43:56 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * operator_token
 * extract and tag the operator token from the input line, if present
 * @param remaining - pointer to the remaining part of the input line 
 * after extracting the operator
 * @param line - current line
*/
t_token	*operator_token(char **remaining, char *line)
{
	static char *const	operators[] = \
	{"||", "&&", ";", "|", "(", ")", "\n", NULL};
	int					i;
	char				*operator;

	i = 0;
	while (operators[i] != NULL)
	{
		if (check_prefix(line, operators[i]))
		{
			operator = ft_strdup(operators[i]);
			if (operator == NULL)
				tk_error_manager("ft_strdup failed");
			*remaining = line + ft_strlen(operator);
			return (create_token(operator, TK_OPERATOR));
		}
		i++;
	}
	tk_error_manager("Unrecognized operator");
	return (NULL);
}

/**
 * * redirect_token
 * extract and tag redirect token from the input line, if present
 * @param remaining - pointer to the remaining part of the input line 
 * after extracting the redirect
 * @param line - current line
*/
t_token	*redirect_token(char **remaining, char *line)
{
	static char *const	redirects[] = {"<" ">" "<<" ">>", NULL};
	int					i;
	char				*redirect;

	i = 0;
	while (redirects[i] != NULL)
	{
		if (check_prefix(line, redirects[i]))
		{
			redirect = ft_strdup(redirects[i]);
			if (redirect == NULL)
				tk_error_manager("ft_strdup failed");
			*remaining = line + ft_strlen(redirect);
			return (create_token(redirect, TK_REDIRECT));
		}
		i++;
	}
	tk_error_manager("Unrecognized operator");
	return (NULL);
}

t_token	*word_token(char **remaining, char *line)
{
	char	*start;
	char	*returnword;
	bool	quote_flag;
	int		i;

	start = line;
	quote_flag = false;
	i = -1;
	while (line[++i] != '\0' && !is_metacharacter(line[i]) \
			&& !ft_isspace(line[i]))
	{
		if (line[i] == '\\')
			i += 2;
		else if (line[i] == '\'' || line[i] == '\"')
		{
			check_missingquotes(&line, &quote_flag, line[i]);
			if (quote_flag)
				break ;
		}
	}
	returnword = ft_strndup(start, line - start);
	if (returnword == NULL)
		tk_error_manager("ft_strndup failed");
	*remaining = line;
	return (create_token(returnword, TK_WORD));
}

t_token	*create_token(char *word, t_tk_kind kind)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		tk_error_manager("Calloc failed");
	token->word = word;
	token->kind = kind;
	return (token);
}