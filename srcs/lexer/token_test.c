/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:21:46 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/04 01:59:29 by jdagoy           ###   ########.fr       */
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

const char *error_invalid[] = {
	"cat %",
	"cat !",
	"cat > @",
	"cat # > a",
	NULL
};

const char *error_redirect[] = {
	"cat >",
	"cat>",
	"cat <",
	"cat<",
	"cat <<<",
	"cat<<<",
	"cat >>>",
	"cat>>>",
	"cat > &&",
	"cat > ||",
	"cat > ;",
	NULL
};

const char *error_operator[] = {
	"cat ||",
	"cat &&",
	"cat ;",
	"cat |",
	"cat && >",
	"cat | ||",
	"cat ||||",
	"cat | ;",
	// "( || )",
	"cat || &&",
	"cat || |",
	"cat && ;",
	NULL
};

const char *error_word[] = {
	"echo \"hello\"world\"",
	"echo \"hello\\\"",
	"echo \\x"
};

void	free_token(t_token *head);

int main(void)
{
	t_token		*tokens;
	int			i;
	char		*line;
	const char		**error_tests[] = {error_invalid, error_redirect, error_operator, error_operator, NULL};
	const char		*tests[] = {"error_invalid", "error_redirect", "error_operator", "error_operator"};

	for (int i = 0; error_tests[i] != NULL; i++)
	{
		printf("%s\n", tests[i]);
		for (int j = 0; error_tests[i][j] != NULL; j++)
		{
			printf("Input: %s\n", (char *)error_tests[i][j]);
			tokens = tokenizer((char *)error_tests[i][j]);
			if (check_tokens(tokens) == false || check_wordtokens(tokens) == false)
			{
				free_token(tokens);
			}
			while (tokens != NULL && tokens->kind != TK_EOF)
			{
				printf("Token %d\n", j);
				printf("Token: \t%s\n", tokens->word);
				printf("Kind: \t%s", token_kind_strings[tokens->kind]);
				tokens = tokens->next;
			}
			free_token(tokens);
			printf("\n");
		}
		printf("====================\n\n");
	}

	while (1)
	{
		i = 0;
		line = readline("Token_tester > ");
		// printf("%s\n", line);
		tokens = tokenizer(line);
		while (tokens != NULL && tokens->kind != TK_EOF)
		{
			printf("Token %d\n", i);
			printf("Token: \t%s\n", tokens->word);
			printf("Kind: \t%s", token_kind_strings[tokens->kind]);
			tokens = tokens->next;
		}
		free_token(tokens);
		free(line);
	}
	return (0);
}

void	free_token(t_token *head)
{
	t_token	*itr;
	t_token	*next;

	if (head == NULL)
		return ;
	itr = head;
	next = itr->next;
	while (next != NULL)
	{
		free(itr->word);
		free(itr);
		itr = next;
		next = itr->next;
	}
	free(itr->word);
	free(itr);
}
