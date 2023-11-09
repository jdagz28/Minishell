/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:07:35 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/09 11:47:16 by jdagoy           ###   ########.fr       */
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
bool	build_ast(t_token **tokens, t_node **ast, bool is_subshell)
{
	bool	ret;

	ret = 0;
	while (*tokens != NULL)
	{
		if (is_logical_operator((*tokens)->kind))
		{
			if (*ast == NULL)
				return (false);
			ret = parse_logical_operator(tokens, ast, is_subshell);
		}
		else
			ret = parse_pipeline(tokens, ast, is_subshell);
		if (ret == false)
			return (false);
	}
	return (true);
}