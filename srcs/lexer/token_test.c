/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:21:46 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/05 00:32:29 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

const char *token_kind_strings[] = {
    "TK_OPERATOR",
    "TK_REDIRECT",
    "TK_WORD",
    // "TK_OPTION_COMMAND",
    // "TK_REDIRECT_LEFT",
    // "TK_REDIRECT_RIGHT",
    // "TK_REDIRECT_HEREDOC",
    // "TK_REDIRECT_APPEND",
    // "TK_PIPE",
    // "TK_SINGLE_QUOTE",
    // "TK_DOUBLE_QUOTE",
    // "TK_VARIABLE",
    // "TK_BACKSLASH",
    // "TK_SEMICOLON",
    // "TK_LITERAL",
    "TK_EOF"
};

void	free_token(t_token *head);

int main(int argc, char **argv)
{
	t_token		*tokens;
	// int			i;
	// char		*line;

	if (argc != 2)
	{	
		printf("Usage: %s script\n", argv[0]);
		return (1);
	}
	printf("Input: %s\n", argv[1]);
	tokens = tokenizer(argv[1]);
	if (check_tokens(tokens) == false || check_wordtokens(tokens) == false)
		free_token(tokens);
	else
	{
		while (tokens != NULL)
		{
			printf("Token: \t%s\n", tokens->word);
			printf("Kind: \t%s", token_kind_strings[tokens->kind]);
			tokens = tokens->next;
		}
		free_token(tokens);
		printf("\n");
	}
	// while (1)
	// {
	// 	i = 0;
	// 	line = readline("Token_tester > ");
	// 	tokens = tokenizer(line);
	// 	while (tokens != NULL && tokens->kind != TK_EOF)
	// 	{
	// 		printf("Token %d\n", i);
	// 		printf("Token: \t%s\n", tokens->word);
	// 		printf("Kind: \t%s", token_kind_strings[tokens->kind]);
	// 		tokens = tokens->next;
	// 	}
	// 	free_token(tokens);
	// 	free(line);
	// }
	return (0);
}

void free_token(t_token *head)
{
    t_token *itr;
    t_token *next;

    if (head == NULL)
        return;

    itr = head;
    while (itr != NULL)
    {
        next = itr->next;
        free(itr->word);
        free(itr);
        itr = next;
    }
}

