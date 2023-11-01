/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:21:46 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/01 22:31:08 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

const char *token_kind_strings[] = {
    "TK_OPERATOR",
    "TK_REDIRECT",
    "TK_WORD",
    "TK_OPTION_COMMAND",
    "TK_REDIRECT_LEFT",
    "TK_REDIRECT_RIGHT",
    "TK_REDIRECT_HEREDOC",
    "TK_REDIRECT_APPEND",
    "TK_PIPE",
    "TK_SINGLE_QUOTE",
    "TK_DOUBLE_QUOTE",
    "TK_VARIABLE",
    "TK_BACKSLASH",
    "TK_SEMICOLON",
    "TK_LITERAL",
    "TK_EOF"
};

int main(int argc, char **argv)
{
	char	*input;
	t_token	tokens;
	int		i;

	while (1)
	{
		i = 0;
		line = readline("Token_tester > ");
		tokens = tokenizer(line);
		while (tokens != NULL && tokens->kind = TK_EOF)
		{
			printf("Token %d\n", i);
			printf("Token: \t%s\n", tokens->word);
			printf("Kind: \t%s", token_kind_strings[tokens->kind])
			tokens = tokens->next;
		}
		free(line);
	}
	free(tokens);
	return (0);
}

