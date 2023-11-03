/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 00:33:45 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/03 05:56:15 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

bool not_escaped(const char *args)
{
    size_t position = 0;
    while (args[position] != '\0')
    {
        if ((args[position] == '\'' || args[position] == '\"') && (position == 0 || args[position - 1] != '\\'))
        {
            return true;
        }
        position++;
    }
    return false;
}

bool	check_quotes(char *str)
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

bool	check_word(char **str)
{
	char	*word;

	word = *str;
	if (ft_strchr(*str, '\'') || ft_strchr(*str, '\"'))
		if (check_quotes(*str))
			return (check_word_inquote(str, *str));
	while (*word != '\0')
	{
		if (*word == '\\')
		{
			word++;
			if (*word == '\0')
			{
				tk_error_manager("Invalid syntax: newline after escape char");
				return (false);
			}
		}
		word++;
	}
	return (true);
}


bool	check_backslashescape(char *str)
{
	if (str[0] == '\\' && (str[1] == '\"' || str[1] == '\'' 
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
			if (check_word(&str))
				return (false);
		token = token->next;
	}
	return (true);
}