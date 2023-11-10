/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_logical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:23:44 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/09 11:59:37 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * is_logical_operator
 * check if the current token is a logical operator
*/
bool	is_logical_operator(enum e_tk_kind kind)
{
	if (kind == TK_OR || kind == TK_AND || kind == TK_SEMICOLON)
		return (true);
	return (false);
}

/**
 * * parse_logical_operator
 * handles logical operator tokens, create a corresponding node in the AST,
 * organizes the tree structure by transfering the left child of the node from
 * the provided AST. The right child is created by parsing the pipeline
*/
bool	parse_logical_operator(t_token **tokens, t_node **ast, bool is_subshell)
{
	t_node	*logical_node;

	if (*ast == NULL)
		return (false);
	logical_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (logical_node == NULL)
		return (false);
	logical_node->type = (enum e_node_type)(*tokens)->kind;
	logical_node->content.child.left = *ast;
	*ast = logical_node;
	consume_token(tokens);
	if (*tokens == NULL)
	{
		if (logical_node->type == SEMICOLON_NODE)
			return (true);
		else
		{
			ft_putstr_fd("\nminishell: syntax error: unexepected end of file\n", \
				STDERR_FILENO);
			return (false);
		}
	}
	return (parse_pipeline(tokens, &(logical_node->content.child.right), \
							is_subshell));
}
