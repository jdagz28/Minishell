/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 02:59:10 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/16 09:37:03 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"
#include "expansion.h"

const char *token_kind_strings[] = {
	"TK_WORD",
	"TK_PIPE",
	"TK_OR",
	"TK_AND",
	"TK_SEMICOLON",
	"TK_OPEN_PARENTHESIS",
	"TK_CLOSE_PARENTHESIS",
	"TK_OPERATOR",
	"TK_REDIRECT",
	"TK_EOF"};
void	print_tokens(t_token *tokens);

int main(void)
{
	t_token	*tokens;
	t_node	*ast;
	char	*line;

	setenv("hello", "Hello, world!", 1);
	
	line = "echo $hello";
	printf("var: %s\n", getenv("hello"));
	tokens = tokenizer(line);
	if (check_tokens(tokens) == false || check_wordtokens(tokens) == false)
	{
		clear_tokens(tokens);
		// continue ;
	}
	print_tokens(tokens);
	if (build_ast(&tokens, &ast) == false)
		if (tokens)
			printf("\nminishell: syntax error near unexpected token '%s'\n", \
					tokens->word);
	printf("Before expansion: ");
	for (int i = 0; ast->content.simple_cmd.argv[i] != NULL; i++)
		printf("%s ", ast->content.simple_cmd.argv[i]);
	printf("\n");
	if (expand_cmds(ast) == false)
		printf("Error in expansion\n");
	printf("After expansion: ");
	for (int i = 0; ast->content.simple_cmd.argv[i] != NULL; i++)
		printf("%s ", ast->content.simple_cmd.argv[i]);
	printf("\n");
	if (tokens != NULL)
		clear_tokens(tokens);
	if (ast != NULL)
		clear_ast(&ast);
}

void	print_tokens(t_token *tokens)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens;
	while (current != NULL)
	{
		printf("Token %d\n", i++);
		if (current->word != NULL)
			printf("Token: \t%s\n", current->word);
		printf("Type: \t%s\n\n", token_kind_strings[current->kind]);
		current = current->next;
	}
}
