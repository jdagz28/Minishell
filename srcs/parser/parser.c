/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:07:35 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/09 09:57:34 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * clear_tokens
 * free the tokens list
 * iterates through the list and frees the word and token itself
*/
void	clear_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;
	
	if (tokens == NULL)
		return ;
	current = *tokens;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
	*tokens = NULL;
}

/**
 * * is_redirect_word
 * checks if the token is TK_WORD or TK_REDIRECT which is typically 
 * a part of a simple command
*/
bool	is_redirect_word(enum e_tk_kind kind)
{
	if (kind == TK_WORD || kind == TK_REDIRECT)
		return (true);
	return (false);
}

/**
 * * num_args
 * counts the number of arguments in the tokens list
 * iterates throught the list and increments the count as long as the tokens
 * have TK_WORD or TK_REDIRECT kind, part of a simple command 
*/
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

/**
 * * extract_tokens
 * extract tokens enclosed within a pair of opening and closing parentheses
*/
t_token	*extract_tokens(t_token *tokens)
{
	int		pthesis_count;
	t_token	*previous;

	pthesis_count = 1;
	previous = tokens;
	tokens = tokens->next;
	while (tokens)
	{
		if (tokens->kind == TK_OP_PAREN)
			pthesis_count++;
		else if (tokens->kind == TK_CL_PAREN)
		{
			pthesis_count--;
			if (pthesis_count == 0)
				return (tokens);
		}
		previous = tokens;
		tokens = tokens->next;
	}
	return (NULL);
}

/**
 * * build_subtree
 * build a subtree within the larger AST based on tokens enclosed in parenthesis
*/
bool	build_subtree(t_token **tokens, t_token **sub_tokens, t_node **sub_tree)
{
	if (*tokens != NULL && (is_redirect_word((*tokens)->kind) == true \
		|| (*tokens)->kind == TK_OP_PAREN))
	{
		if (build_ast(sub_tokens, sub_tree) == false)
		{
			clear_tokens(sub_tokens);
			return (false);
		}
	}
	return (true);
}

/**
 * *parse_parenthesis
 * parse tokens after an opening parenthesis and beffore a closing parenthesis
 * ensures proper matching of opening and closing parenthesis and constructs a subtree
 * for the enclosed tokens, which is then attached to the parent AST
*/
bool	parse_parenthesis(t_token **tokens, t_node **ast)
{
	t_token *before_closing_parenthesis;
	t_node	*sub_tree;
	t_token	*sub_token_list;

	if ((*tokens)->next != NULL && (*tokens)->next->kind == TK_CL_PAREN)
	{
		consume_token(tokens);
		return (false);
	}
	before_closing_parenthesis = extract_tokens(*tokens);
	consume_token(tokens);
	if (before_closing_parenthesis == NULL)
	{
		clear_tokens(tokens);
		ft_putstr_fd("\nminishell: syntax error near unexpected token `)'\n",\
					STDERR_FILENO);
		return (false);
	}
	sub_token_list = *tokens;
	*tokens = before_closing_parenthesis->next->next;
	free(before_closing_parenthesis->next->word);
	free(before_closing_parenthesis);
	if (build_sub_tree(tokens, &sub_token_list, &sub_tree) == false)
		return (false);
	clear_tokens(sub_token_list);
	*ast = sub_tree;
	if (*tokens != NULL && (*tokens)->kind == TK_PIPE)
		return (false);
	return (true);
}

/**
 * * parse_cmdargs
 * parses the arguments and I/O redirections of a simple command
 * constructs and populates the argv array of a simple command node in the AST by
 * extracting arguments and handling I/O redirections.
 * extracts arguments from the tokens list and sets up redirections if necessary
*/
bool	parse_cmdargs(t_token **tokens, t_node *simple_cmd)
{
	int	i;

	i = 0;
	simple_cmd->content.simple_cmd.argv = (char **)ft_calloc(1, sizeof(char *) \
		* (num_args(*tokens) + 1));
	if (simple_cmd->content.simple_cmd.argv == NULL)
		return (false);
	while (*tokens != NULL && is_redirect_word((*tokens)->kind))
	{
		if ((*tokens)->kind == TK_REDIRECT && (*tokens)->next == NULL \
			|| (*tokens)->next->kind != TK_WORD)
		{
			consume_token(tokens);
			if (*tokens == NULL)
			{
				ft_putstr_fd("\nminishell: syntax error near unexpected token \
					`newline'\n", STDERR_FILENO);
				return (false);
			}
			if ((*tokens)->kind != TK_WORD)
				return (false);
		}
		simple_cmd->content.simple_cmd.argv[i++] = ft_strdup((*tokens)->word);
		if (simple_cmd->content.simple_cmd.argv[i] == NULL)
			return (false);
		consume_token(tokens);
	}
	simple_cmd->content.simple_cmd.argv[i] = NULL;
	return (true);
}

/**
 * * parse_simple_cmd
 * parses a simple command, which typically represents a leaf node in the AST
 * checks if the current tokens form a simple command or leaf node of the AST. 
 * If the tokens are part of as simple command, it constructs the simple 
 * command node including its arguments and I/O redirections
 * parse_cmdargs fills the argv array of the simple_cmd 
*/
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
		return (false);
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
	if (tokens->kind == TK_OP_PAREN)
		return (false);
	return (true);
}

/**
 * * parse_pipeline
 * handle pipe tokens, creating corresponding nodes in the AST.
 * a pipeline is a sequence of one or more simple commands separated by the pipe token
 * it organizes the tree structure by transferring the left child of the node from
 * the provided AST. The right child is created by parsing the subsequent simple command.
 * * if a pipe token is found after the first simple command,
 * * it will loop with the following flow
 * * pipe token is consumed
 * * if the token list is empty, nothing follows the pipe token, then syntax error
 * * pipe_node is allocated and initialized
 * * if the token list is not empty, parse_simple_cmd is called to parse the next simple command
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
			return (false);
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
 * free the current token and move to the succeeding token
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
 * handles logical operator tokens, create a corresponding node in the AST,
 * organizes the tree structure by transfering the left child of the node from
 * the provided AST. The right child is created by parsing the pipeline
*/
bool	parse_logical_operator(t_token **tokens, t_node **ast)
{
	t_node	*logical_node;
	
	if (*ast == NULL)
		return (false);
	logical_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (logical_node == NULL)
		return (false);
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
*/
bool	is_logical_operator(enum e_tk_kind kind)
{
	if (kind == TK_OR || kind == TK_AND || kind == TK_SEMICOLON)
		return (true);
	return (false);
}

/**
 * * build_ast
 * builds the Abstract Syntax Tree (AST) based on a linked list of tokens.
 * depending on the token kind, the corresponding function is called to parse
 * the token and build the appropriate AST node
*/

bool	build_ast(t_token **tokens, t_node **ast)
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