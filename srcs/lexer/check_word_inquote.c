/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_word_inquote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 23:44:50 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/04 00:04:06 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

static void skip_quoted(char **str)
{
	char	type;

	type = **str;
	(*str)++;

	while (**str != '\0' && **str != type)
	{
		if (**str == '\\')
			(*str)++;
		(*str)++;	
	}
	if (**str == type)
		(*str)++;
}

bool	check_word_inquote(char *str)
{
	while (*str != '\0')
	{
		while (*str != '\'' && *str != '\"')
		{
			if (*str == '\0')
				return (true);
			if (*str == '\\')
				str++;
			str++;	
		}
		skip_quoted(&str);
		if (*str == '\0')
		{
			tk_error_manager("Invalid syntax: newline after escape char");
			return (false);
		}
		str++;
	}
	return (true);
}	
