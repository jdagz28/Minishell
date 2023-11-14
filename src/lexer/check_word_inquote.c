/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word_inquote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:44:50 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/14 02:16:42 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

bool	word_error(char *s, size_t len)
{
	if (s[len - 1] == '\\')
	{
		tk_error("syntax error near newline ' ", "\\n");
		return (false);
	}
	tk_error("syntax error near quote '", s);
	return (false);
}

static void	skip_escape(char **str)
{
	if (**str == '\\')
		(*str)++;
	(*str)++;
}

bool	check_word_inquote(char **word, char *tmp_str)
{
	char	type;

	while (**word != '\0')
	{
		while (**word != '\'' && **word != '\"')
		{
			if (**word == '\0')
				return (true);
			skip_escape(&(*word));
		}
		type = **word;
		(*word)++;
		while (**word != type && **word != '\0')
			skip_escape(&(*word));
		if (**word == '\0')
			return (word_error(tmp_str, ft_strlen(tmp_str)));
		(*word)++;
	}
	return (true);
}
