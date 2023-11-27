/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:54:17 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/27 21:03:43 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

static void	parse_error(t_token* tokens, int error)
{
	if (error == 1)
	{
		if (tokens)
			printf("\nminishell: syntax error near unexpected token '%s'\n", \
				tokens->word);
	}
	free_token(tokens);
	set_exit_value(SYNTAX_ERROR);
}

t_node	*parse(char *line, t_shell *shell)
{
	t_token* tokens;
	t_node* ast;

	if (!line)
		return (NULL);
	ast = NULL;
	tokens = tokenizer(line);
	if (check_tokens(tokens) == false || check_wordtokens(tokens) == false)
	{
		parse_error(tokens, 0);
		return (NULL);
	}
	if (build_ast(&tokens, &ast) == false)
	{
		parse_error(tokens, 1);
		return (NULL);
	}
	expand_cmds(ast, shell);
	shell->err = *get_exit_value();
	free_token(tokens);
	return (ast);
}
