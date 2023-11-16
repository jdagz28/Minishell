/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:28:24 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/15 15:42:17 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * check_error_cmdargs
 * print error if redirect is followed by NULL token
 * if in_subshell, within parenthesis -- before closing parenthesis
 * else -- unexpected 'newline' token
*/
static bool	error_cmdargs(void)
{
	ft_putstr_fd("\nminishell: syntax error near unexpected token \
						'newline'\n", STDERR_FILENO);
	return (false);
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
static unsigned int	num_args(t_token *tokens)
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
 * * parse_cmdargs
 * parses the arguments and I/O redirections of a simple command
 * constructs and populates the argv array of a simple command node in the AST by
 * extracting arguments and handling I/O redirections.
 * extracts arguments from the tokens list and sets up redirections if necessary
*/
static bool	parse_cmdargs(t_token **tokens, t_node *simple_cmd)
{
	int	i;

	i = 0;
	simple_cmd->content.simple_cmd.argv = (char **)ft_calloc(1, sizeof(char *) \
		* (num_args(*tokens) + 1));
	if (simple_cmd->content.simple_cmd.argv == NULL)
		return (false);
	while (*tokens != NULL && is_redirect_word((*tokens)->kind))
	{
		if ((*tokens)->kind == TK_REDIRECT && ((*tokens)->next == NULL \
			|| (*tokens)->next->kind != TK_WORD))
		{
			consume_token(tokens);
			if (*tokens == NULL)
				return (error_cmdargs());
			if ((*tokens)->kind != TK_WORD)
				return (false);
		}
		simple_cmd->content.simple_cmd.argv[i] = ft_strdup((*tokens)->word);
		if (simple_cmd->content.simple_cmd.argv[i++] == NULL)
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
		return (false);
	if (is_redirect_word((*tokens)->kind) == false)
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
