/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 00:33:45 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/11 21:12:14 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

static bool	check_quotes(char *str)
{
	int	position;

	position = 0;
	while (str[position] != '\0')
	{
		if (str[position] == '\'' || str[position] == '\"')
		{
			if (position == 0)
				return (true);
			if (position != 0 && str[position - 1] != '\\')
				return (true);
		}
		str++;
	}
	return (false);
}

static bool	check_word(char **str)
{
	char	*word;

	word = *str;
	if (ft_strchr(*str, '\'') || ft_strchr(*str, '\"'))
		if (check_quotes(*str))
			return (check_word_inquote(&(*str), word));
	while (*word != '\0')
	{
		if (*word == '\\')
		{
			word++;
			if (*word == '\0')
				return (word_error(word, ft_strlen(word)));
		}
		word++;
	}
	return (true);
}

static bool	check_backslashescape(char *str)
{
	if (str[0] == '\\' && (str[1] == '\"' || str[1] == '\'' \
		|| str[1] == '\\') && str[2] == '\0')
		return (true);
	return (false);
}

bool	check_wordtokens(t_token *token)
{
	char	*str;

	while (token != NULL && token->kind != TK_EOF)
	{
		str = token->word;
		if (check_backslashescape(str) == false)
			if (check_word(&str) == false)
				return (false);
		token = token->next;
	}
	return (true);
}