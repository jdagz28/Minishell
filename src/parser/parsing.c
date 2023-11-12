/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:54:17 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/09 21:33:15 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *parse(char *line)
{
	t_token *tokens;
	t_node *ast;

	if (!line)
		return (NULL);
	ast = NULL;
	tokens = tokenizer(line);
	// print_tokens(tokens);
	if (check_tokens(tokens) == false || check_wordtokens(tokens) == false)
	{
		printf("Error: invalid token\n");
		free_token(tokens);
		return (NULL);
	}
	if (build_ast(&tokens, &ast, false) == false)
	{
		if (tokens)
			printf("\nminishell: syntax error near unexpected token '%s'\n",
				   tokens->word);
		return (NULL);
	}
	free_token(tokens);
	return (ast);
}

/*
int main()
{
	char *line;
	t_node *ast;
	int cmd_index;

	cmd_index = 1;
	while (1)
	{
		line = readline("LexParser_Test> ");
		ast = parsing(line);
		print_ast_recursive(ast);
		clear_ast(&ast);
		free(line);
		cmd_index++;
	}
}
*/