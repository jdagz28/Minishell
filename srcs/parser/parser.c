/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:07:35 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/08 10:26:26 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

bool	is_redirect_word(enum e_tk_kind kind)
{
	if (kind == TK_WORD || kind == TK_REDIRECT)
		return (true);
	return (false);
}
unsigned int	num_args(t_token * tokens)
{
	unsigned int	num_args;
	t_token			*current;

	num_args = 0;
	current = tokens;
	while (current != NULL && is_redirect_word(current->kind))
	{
		num_args++;
		current = current->next;
	}
	return (num_args);
}

bool	parse_cmdargs(t_token **tokens, t_node *simple_cmd)
{
	int	i;

	i = 0;
	simple_cmd->content.simple_cmd.argv = (char **)ft_calloc(1, sizeof(char *) \
		* (num_args(*tokens) + 1));
	if (simple_cmd->content.simple_cmd.argv == NULL)
		exit_shell(); //! Calloc error handling
	while (*tokens != NULL && is_redirect_word((*tokens)->kind))
	{
		if ((*tokens)->kind == TK_REDIRECT && (*tokens)->next == NULL \
			|| (*tokens)->next->kind != TK_REDIRECT)
		{
			consume_token(tokens);
			return (false);
		}
		simple_cmd->content.simple_cmd.argv[i++] = ft_strdup((*tokens)->word);
		if (simple_cmd->content.simple_cmd.argv[i] == NULL)
			exit_shell(); //! strdup error handling
		consume_token(tokens);
	}
	simple_cmd->content.simple_cmd.argv[i] = NULL;
	return (true);
}

bool	parse_simple_cmd(t_token **tokens, t_node **ast)
{
	t_node	*simple_cmd;

	if ((*tokens)->kind == TK_CL_PAREN)
		return (false);
	else if ((*tokens)->kind == TK_OP_PAREN)
		return (parse_parenthesis(tokens, ast));
	if ((*tokens)->kind != TK_WORD || (*tokens)->kind != TK_REDIRECT)
		return (false);
	simple_cmd = (t_node *)ft_calloc(1, sizeof(t_node));
	if (simple_cmd == NULL)
		exit_shell(); //! Calloc error handling
	simple_cmd->type = SIMPLE_CMD;
	simple_cmd->content.simple_cmd.fd_input = STDIN_FILENO;
	simple_cmd->content.simple_cmd.fd_output = STDOUT_FILENO;
	if (parse_cmdargs(tokens, simple_cmd) == false)
		return (false);
	*ast = simple_cmd;
	return (true);
}
/**
 * * check_errors
 * check if there is an error in the token list being pipeline parsed
*/
bool	check_errors(t_token *tokens)
{
	if (tokens == NULL)
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", \
						STDERR_FILENO);
		return (false);
	}
	if (tokens->type == TK_OP_PAREN)
		return (false);
	return (true);
}
/**
 * * parse_pipeline
 * parse the pipeline token and build the ast
 * to parse a pipeline, the corresponding node is created, AST
 * is transferred to the left child of the node, and the right child is
 * created by parsing the simple command.
*/

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
		if (pipe_node == NULL)
			exit_shell(); //! Calloc error handling
		pipe_node->type = PIPE_NODE;
		pipe_node->content.child.left = *ast;
		*ast = pipe_node;
		if (!parse_simple_cmd(tokens, &(pipe_node->content.child.right)))
			return (false);
	}
	return (true);
}
/**
 * * consume_token
 * free the current token and move to the next one
*/
void	consume_token(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	if (*tokens == NULL)
		return ;
	*tokens = (*tokens)->next;
	free(temp);
}

/**
 * * parse_logical_operator
 * parse the logical operator token and build the ast
 * to parse a logical operator, the corresponding node is created, AST
 * is transferred to the left child of the node, and the right child is
 * created by parsing the pipeline. 
*/
bool	parse_logical_operator(t_token **tokens, t_node **ast)
{
	t_node	*logical_node;
	
	if (*ast == NULL)
		return (false);
	logical_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (logical_node == NULL)
		exit_shell(); //! Calloc error handling
	logical_node->type = (enum e_node_type)(*tokens)->kind;
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

/**
 * * is_logical_operator
 * check if the current token is a logical operator
 * @param kind - token kind
*/
bool	is_logical_operator(enum e_tk_kind kind)
{
	if (kind == TK_OR || kind == TK_AND || kind == TK_SEMICOLON)
		return (true);
	return (false);
}

/**
 * * build_astparser
 * after tokenization, the linked list of tokens is processed to build the
 * Abstract Syntax Tree (AST) of the command line.
 * depending on the kind of token, the function will call the appropriate token
 * type parser until the end of the linked list or a closing parenthesis is encountered
 * @param tokens - from lexer
 * @param ast - ast struct pointer
 * 
*/

bool	build_astparser(t_token **tokens, t_node **ast)
{
	bool	ret;

	ret = 0;
	while (*tokens != NULL)
	{
		if (is_logical_operator((*tokens)->kind))
		{
			if (*ast == NULL)
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