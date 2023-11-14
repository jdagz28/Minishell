/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:28:37 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/14 02:17:02 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * consume_token
 * free the current token and move to the succeeding token
*/
void	consume_token(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	if (*tokens == NULL)
		return ;
	*tokens = (*tokens)->next;
	free(temp);
}

/**
 * * clear_tokens
 * free the tokens list
 * iterates through the list and frees the word and token itself
*/
void	clear_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (tokens == NULL)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
	*tokens = NULL;
}
