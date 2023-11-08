/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:54:17 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/08 10:45:03 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

const char *token_kind_strings[] = {
    "TK_WORD",
	"TK_OR",
	"TK_AND",
	"TK_SEMICOLON",
	"TK_OPEN_PARENTHESIS",
	"TK_CLOSE_PARENTHESIS",
	"TK_OPERATOR",
	"TK_REDIRECT",
	"TK_EOF"
};

void	free_token(t_token *head);
void	print_tokens(t_token *tokens);

int main(int argc, char **argv)
{
	t_token		*tokens;
	t_node		*ast;

	if (argc != 2)
	{
		printf("Usage: %s script\n", argv[0]);
		return (1);
	}
	printf("Input: %s\n", argv[1]);
	tokens = tokenizer(argv[1]);
	print_tokens(tokens);
	(void)ast;
	// if (build_astparser(tokens, ast) == false)
	// {
	// 	printf("Error: building the abstract syntax tree\n");
	// 	return (1);
	// }
	return (0);
}

void	free_token(t_token *head)
{
	t_token	*itr;
	t_token	*next;

	if (head == NULL)
		return ;
	itr = head;
	while (itr != NULL)
	{
		next = itr->next;
		if (itr)
			free(itr);
		itr = next;
	}
}
void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		printf("Token %d\n", i);
		printf("Token: \t%s\n", tokens->word);
		printf("Type: \t%s\n", token_kind_strings[tokens->kind]);
		tokens = tokens->next;
	}
}