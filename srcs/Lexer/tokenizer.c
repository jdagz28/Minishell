/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:09:27 by jdagoy            #+#    #+#             */
/*   Updated: 2023/10/31 22:21:37 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

//! Tokenize first on major types: operator, redirect, word
//! Process further tokens to tag appropriate token types


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
		return (NULL); //!Handle error - malloc failed
	head.next = NULL;
	current = &head;
	while (*line)
	{
		//TODO
		//1. Check for whitespaces and consume whitespaces;
		//2. Check if operator - "||", "&", "&&", ";", ";;", "(", ")", "|", "\n"
		//3. Check if redirect - "<" ">" "<<" ">>"
		//4. Check if word 
		//5. If not among the types - handle unknown token
		if (check_whitespace(&line, line))
			continue ;
		else if (is_operator(line))
			current->next = operator_type(&line, line);
		else if (is_redirect(line))
			current->next = redirect_type(&line, line);
		else if (is_word(line))
			current->next = word_type(&line, line);
		else
			printf("Unexpected Token\n");
		current = current->next;
	}
	// Create last token to have the TK_EOF;
	current->next = new_token(NULL, TK_EOF);
	return (head.next);

}

/**
 * * check_whitespace
 * check for whitespaces; skip if there are any
 * @param next_inline - line pointer
 * @param line - current line
 */
bool 	check_whitespace(char **next_inline, char *line)
{
	int	i;

	i = 0;
	if (ft_isspace(line[i]))
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		*next_inline = line[i];
		return (true);	
	}
	return (false);
}


/**
 * * is_operator
 * check if line is either one of the ff
 * "||", "&", "&&", ";", ";;", "(", ")", "|", "\n"
 * @param line	- current line
 */
bool	is_operator(char *line)
{
	
}

/**
 * * is_redirect
 * check if line is a redirect
 * "<" ">" "<<" ">>"
 * @param line	- current line
 */