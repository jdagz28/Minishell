/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:09:27 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/30 15:34:36 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

static void	tokenizer_error(char *error_msg, char **remaining, char *current)
{
	set_exit_value(SYNTAX_ERROR);
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	while (*current)
		current++;
	*remaining = current;
}
/**
 * * Tokenizer
 * Tokenize input from readline, check each character for token type
 * Stores tokens in a linked list
 * @param input
 */

t_token	*tokenizer(char *line)
{
	t_token	head;
	t_token	*current;

	head.next = NULL;
	current = &head;
	while (*line)
	{
		if (check_whitespace(&line, line))
			continue ;
		else if (is_operator(line) || is_redirect(line) || is_word(line))
		{
			if (is_operator(line))
				current->next = operator_token(&line, line);
			else if (is_redirect(line))
				current->next = redirect_token(&line, line);
			else if (is_word(line))
				current->next = word_token(&line, line);
			current = current->next;
		}
		else
			tokenizer_error("Unexpected Token", &line, line);
	}
	current->next = create_token(NULL, TK_EOF);
	return (head.next);
}
