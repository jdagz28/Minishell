/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:34:48 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/11 22:29:08 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * check_whitespace
 * check for whitespaces; skip if there are any
 * @param next_inline - line pointer
 * @param line - current line
 */
bool	check_whitespace(char **next_inline, char *line)
{
	if (ft_isspace(*line))
	{
		while (*line && ft_isspace(*line))
			line++;
		*next_inline = line;
		return (true);
	}
	*next_inline = line;
	return (false);
}

/**
 *  *check_prefix
 *  helper function for is_operator and is_redirect
 * @param line
 * @param prefix - current operator being check against
*/
bool	check_prefix(char *line, char *prefix)
{
	if (ft_strncmp(line, prefix, ft_strlen(prefix)) == 0)
		return (true);
	return (false);
}

void	tk_error(char *error_msg, char *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if ((ft_strnstr(error_msg, "Calloc", ft_strlen(error_msg)) != NULL) \
		|| (ft_strnstr(error_msg, "ft_strndup", ft_strlen(error_msg)) != NULL))
		exit(EXIT_FAILURE);
}

void	check_missingquotes(char **line, bool *flag, char quote_type)
{
	(*line)++;
	while (**line != quote_type)
	{
		if (**line == '\0')
		{
			*flag = true;
			return ;
		}
		(*line)++;
	}
	(*line)++;
}
