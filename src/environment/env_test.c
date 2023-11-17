/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:14:58 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/17 10:44:45 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"
#include "expansion.h"
#include "builtins.h"

int	main(void)
{
	t_token		*tokens;
	t_node		*ast;
	char		*line;
	int			cmd_index;

	ast = NULL;
	tokens = NULL;
	cmd_index = 1;
	while (1)
	{
		printf("specifically testing for variable:$VAR=VALUE");
		line = readline("LexParser_Test> ");
		tokens = tokenizer(line);
		if (check_tokens(tokens) == false || check_wordtokens(tokens) == false)
		{
			clear_tokens(tokens);
			continue ;
		}
		if (build_ast(&tokens, &ast) == false)
			if (tokens)
				printf("\nminishell: syntax error near unexpected token '%s'\n", \
							tokens->word);
		if (expand_cmds(ast) == false)
			printf("Error in expansion\n");
		if (ast != NULL)
			clear_ast(&ast);
		clear_tokens(tokens);
		free(line);
		cmd_index++;
	}
}