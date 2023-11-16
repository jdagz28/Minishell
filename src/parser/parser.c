/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:07:35 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/11 22:01:56 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * build_ast
 * builds the Abstract Syntax Tree (AST) based on a linked list of tokens.
 * depending on the token kind, the corresponding function is called to parse
 * the token and build the appropriate AST node
 */
bool	build_ast(t_token **tokens, t_node **ast)
{
	bool	ret;

	ret = false;
	while (*tokens && (*tokens)->kind != TK_EOF)
	{
		ret = parse_pipeline(tokens, ast);
		if (ret == false)
			return (false);
	}
	return (true);
}
