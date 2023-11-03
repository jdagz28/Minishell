/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:34:48 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/04 00:16:08 by jdagoy           ###   ########.fr       */
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
	int	i;

	i = 0;
	if (ft_isspace(line[i]))
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		*next_inline = line;
		return (true);	
	}
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

void	tk_error_manager(char *error_msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	check_missingquotes(char **line, bool *flag, char quote_type)
{
	int	i;

	i = 1;
	while ((*line)[i] != quote_type)
	{
		if ((*line)[i] == '\0')
		{
			*flag = true;
			return ;
		}
		i++;
	}
	*line += i;
}