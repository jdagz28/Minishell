/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:28:37 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/28 23:51:11 by jdagoy           ###   ########.fr       */
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
	if (temp->kind != TK_PIPE)
		free(temp->word);
	free(temp);
}
