/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:26:10 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/09 21:38:38 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * check_errors_pipeline
 * check if there is an error in the token list being pipeline parsed
*/
static bool	check_errors_pipeline(t_token *tokens)
{
	if (tokens == NULL)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", \
						STDERR_FILENO);
		return (false);
	}
	if (tokens->kind == TK_OP_PAREN)
		return (false);
	return (true);
}

/**
 * * parse_pipeline
 * handle pipe tokens, creating corresponding nodes in the AST.
 * a pipeline is a sequence of one or more simple commands separated by the 
 * pipe token it organizes the tree structure by transferring the left child 
 * of the node from the provided AST. 
 * The right child is created by parsing the subsequent simple command.
 * * if a pipe token is found after the first simple command,
 * * it will loop with the following flow
 * * pipe token is consumed
 * * if the token list is empty, nothing follows the pipe token, then error
 * * pipe_node is allocated and initialized
 * * if the token list is not empty, parse_simple_cmd is called to parse the 
 * 	next simple command
*/
bool	parse_pipeline(t_token **tokens, t_node **ast, bool is_subshell)
{
	t_node	*pipe_node;
	t_node	*simple_cmd;

	if (parse_simple_cmd(tokens, &simple_cmd, is_subshell) == false)
		return (false);
	*ast = simple_cmd;
	while (*tokens != NULL && (*tokens)->kind == TK_PIPE)
	{
		consume_token(tokens);
		if (check_errors_pipeline(*tokens) == false)
			return (false);
		pipe_node = (t_node *)ft_calloc(1, sizeof(t_node));
		if (pipe_node == NULL)
			return (false);
		pipe_node->type = PIPE_NODE;
		pipe_node->content.child.left = *ast;
		*ast = pipe_node;
		if (!parse_simple_cmd(tokens, &(pipe_node->content.child.right), \
				is_subshell))
			return (false);
	}
	return (true);
}
