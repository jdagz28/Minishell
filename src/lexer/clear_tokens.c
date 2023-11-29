/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:30:08 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/29 20:47:58 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * clear_tokens
 * free the tokens list
 * iterates through the list and frees the word and token itself
*/
void	clear_tokens(t_token *head)
{
	t_token	*itr;
	t_token	*next;

	if (head == NULL)
		return ;
	itr = head;
	next = itr->next;
	while (next != NULL)
	{
		if (itr->kind != TK_PIPE)
			free(itr->word);
		free(itr);
		itr = next;
		next = itr->next;
	}
	if (itr->kind != TK_PIPE)
		free(itr->word);
	free(itr);
}
