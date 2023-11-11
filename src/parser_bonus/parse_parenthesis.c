/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:44:50 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/09 15:25:07 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

/**
 * * extract_tokens
 * extract tokens enclosed within a pair of opening and closing parentheses
*/
static t_token	*extract_tokens(t_token *tokens)
{
	int		pthesis_count;

	pthesis_count = 1;
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
		tokens = tokens->next;
	}
	return (NULL);
}

/**
 * * build_subtree
 * build a subtree within the larger AST based on tokens enclosed in parenthesis
*/
static bool	build_subtree(t_token **tokens, t_token **sub_tokens, \
							t_node **sub_tree)
{
	if (*tokens != NULL && (is_redirect_word((*tokens)->kind) == true \
		|| (*tokens)->kind == TK_OP_PAREN))
	{
		if (build_ast(sub_tokens, sub_tree, true) == false)
		{
			clear_tokens(sub_tokens);
			return (false);
		}
	}
	return (true);
}

static bool	consume_token_return(t_token **tokens)
{
	consume_token(tokens);
	return (false);
}

static void	clear_tokens_and_print(t_token **tokens)
{
	clear_tokens(tokens);
	ft_putstr_fd("\nminishell: syntax error near unexpected token '('\n", \
					STDERR_FILENO);
}

/**
 * *parse_parenthesis
 * parse tokens after an opening parenthesis and beffore a closing parenthesis
 * ensures proper matching of opening and closing parenthesis and constructs a 
 * subtree for the enclosed tokens, which is then attached to the parent AST
*/
bool	parse_parenthesis(t_token **tokens, t_node **ast)
{
	t_token	*before_closing_parenthesis;
	t_node	*sub_tree;
	t_token	*sub_token_list;

	if ((*tokens)->next != NULL && (*tokens)->next->kind == TK_CL_PAREN)
		return (consume_token_return(tokens));
	before_closing_parenthesis = extract_tokens(*tokens);
	consume_token(tokens);
	if (before_closing_parenthesis == NULL)
	{
		clear_tokens_and_print(tokens);
		return (false);
	}
	sub_token_list = *tokens;
	*tokens = before_closing_parenthesis->next->next;
	free(before_closing_parenthesis->next->word);
	free(before_closing_parenthesis);
	if (build_subtree(tokens, &sub_token_list, &sub_tree) == false)
		return (false);
	clear_tokens(&sub_token_list);
	*ast = sub_tree;
	if (*tokens != NULL && (*tokens)->kind == TK_PIPE)
		return (false);
	return (true);
}
