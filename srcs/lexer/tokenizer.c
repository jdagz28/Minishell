/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:09:27 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/03 12:34:38 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * Tokenizer
 * Tokenize input from readline, check each character for token type
 * Stores tokens in a linked list
 * @param input
 */

t_token	*tokenizer(char *input)
{
	char	*line;
	t_token	head;
	t_token	*current;

	line = ft_strdup(input);
	if (line == NULL)
		tk_error_manager("ft_strdup failed");
	head.next = NULL;
	current = &head;
	while (*line)
	{
		if (check_whitespace(&line, line))
			continue ;
		else if (is_operator(line))
			current->next = operator_token(&line, line);
		else if (is_redirect(line))
			current->next = redirect_token(&line, line);
		else if (is_word(line))
			current->next = word_token(&line, line);
		else
			printf("Unexpected Token\n");
		current = current->next;
	}
	current->next = new_token(NULL, TK_EOF);
	return (head.next);
}
