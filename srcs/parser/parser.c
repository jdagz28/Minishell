/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:07:35 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/07 15:46:48 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

bool	parse_pipeline(t_token **tokens, t_node **ast)
{
	t_node	*pipe_node;
	t_node	*simple_cmd;

	if (parse_simple_cmd(tokens, &simple_cmd) == false)
		return (false);
	*ast = simple_cmd;
	while (*tokens != NULL && (*tokens)->kind == TK_PIPE)
	{
		consume_token(tokens);
		if (check_errors(tokens) == false)
			return (false);
		pipe_node = (t_node *)ft_calloc(1, sizeof(t_node));
		pipe_node->type = PIPE_NODE;
		pipe_node->content.child.left = *ast;
		*ast = pipe_node;
		if (!parse_simple_cmd(tokens, &(pipe_node->content.child.right)))
			return (false);
	}
	return (true);
}

void	consume_token(t_token **tokens)
{
	if (*tokens == NULL)
		return ;
	*tokens = (*tokens)->next;
}

bool	parse_logical_operator(t_token **tokens, t_node **ast)
{
	t_node	*logical_node;
	
	if (*ast == NULL)
		return (false);
	logical_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (logical_node == NULL)
		return (false);
	logical_node->type = (enum e_node_type)tokens->kind;
	logical_node->content.child.left = ast;
	*ast = logical_node;
	consume_token(tokens);
	if (*tokens == NULL)
	{
		if (logical_node->type == SEMICOLON_NODE)
			return (true);
		else
		{
			ft_putstr_fd("\nminishell: syntax error: unexepected enf of file\n");
			return (false);
		}
	}
	return parse_pipeline(tokens, &(logical_node->content.child.right));
}

bool	is_logical_operator(enum e_tk_kind kind)
{
	if (kind == TK_OR || kind == TK_AND || kind == TK_SEMICOLON)
		return (true);
	return (false);
}

bool	build_astparser(t_token *tokens, t_node *ast)
{
	bool	ret;
	
	ret = 0;
	while (tokens != NULL)
	{
		if (is_logical_operator(tokens->kind))
		{
			if (ast == NULL)
				return (false);
			ret = parse_logical_operator(tokens, ast);
		}
		else
			ret = parse_pipeline(tokens, ast);
		if (ret == false)
			return (false);
	}
	return (true);
}