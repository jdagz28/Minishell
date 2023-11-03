/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:11:29 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/03 12:29:56 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * is_operator
 * check if line has a control operator and is either one of the ff
 *  "||", "&&", "&", ";", ";;", ";&", ";;&", "|", "|&", "(", ")", "\n"
 * @param line	- current line
 */
bool	is_operator(char *line)
{
	static char *const	operators[] = \
	{"||", "&&", ";", "|", "(", ")", "\n", "NULL"};
	int					i;

	i = 0;
	while (operators[i] != NULL)
	{
		if (check_prefix(line, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

/**
 * * is_redirect
 * check if line is a redirect
 * "<" ">" "<<" ">>"
 * @param line	- current line
 */
bool	is_redirect(char *line)
{
	static char *const	redirect[] = {"<", ">", "<<", ">>", "NULL"};
	int					i;

	i = 0;
	while (redirect[i] != NULL)
	{
		if (check_prefix(line, redirect[i]))
			return (true);
		i++;
	}
	return (false);
}

/**
 * *is_metacharacter
 * check if current character in line is a metachracter
 * ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’. 
 * @param c - current char
*/
bool	is_metacharacter(char c)
{
	return (c && ft_strchr("|;()<>\n", c));
}

/**
 * * is_word
 * check if it just word without metacharacters and whitespaces
 * @param line -current line
*/
bool	is_word(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (is_metacharacter(line[i]) || ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}