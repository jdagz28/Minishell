/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:12:54 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/24 10:25:49 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

t_token	*create_operator_token(char *operator);

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

	i = 0;
	while (operators[i] != NULL)
	{
		if (check_prefix(line, operators[i]))
		{
			*remaining = line + ft_strlen(operators[i]);
			if (ft_strncmp(operators[i], "|", \
					ft_strlen(operators[i])) == 0)
				return (create_token(operators[i], TK_PIPE));
			else
				return (create_token(operators[i], TK_OPERATOR));
		}
		i++;
	}
	tk_error("Unrecognized operator", NULL);
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
	static char *const	redirects[] = {"<<", ">>", "<", ">", NULL};
	int					i;
	char				*redirect;

	i = 0;
	while (redirects[i] != NULL)
	{
		if (check_prefix(line, redirects[i]))
		{
			redirect = ft_strdup(redirects[i]);
			if (redirect == NULL)
				tk_error("ft_strdup failed", NULL);
			*remaining = line + ft_strlen(redirect);
			return (create_token(redirect, TK_REDIRECT));
		}
		i++;
	}
	tk_error("Unrecognized operator", NULL);
	return (NULL);
}

t_token	*word_token(char **remaining, char *line)
{
	char	*start;
	char	*returnword;
	bool	quote_flag;

	start = line;
	quote_flag = false;
	while (*line != '\0' && !is_metacharacter(*line) && !ft_isspace(*line))
	{
		if (*line == '\\')
			line = line + 2;
		else if (*line == '\'' || *line == '\"')
		{
			check_missingquotes(&line, &quote_flag, *line);
			if (quote_flag == true)
				break ;
		}
		else
			line++;
	}
	returnword = ft_strndup(start, line - start);
	if (returnword == NULL)
		tk_error("ft_strndup failed", NULL);
	*remaining = line;
	return (create_token(returnword, TK_WORD));
}

t_token	*create_token(char *word, t_tk_kind kind)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
	{
		free(word);
		tk_error("Calloc failed", NULL);
	}
	token->word = word;
	token->kind = kind;
	return (token);
}
