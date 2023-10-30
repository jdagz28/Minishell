/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:09:27 by jdagoy            #+#    #+#             */
/*   Updated: 2023/10/30 23:58:17 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_parsing.h"


/**
 * * Tokenizer
 * Tokenize input from readline, check each character for token type
 * Stores tokens in a linked list
 * @param line
 */

t_token	*tokenizer(char *line)
{
	t_token	head;
	t_token	*current;
	int		i;

	i = 0;
	head = malloc(sizeof(t_token));
	if (head == NULL)
		return (NULL); //!Handle error - malloc failed
	while (line[i])
	{
		
	}
}
