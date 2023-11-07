/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:07:35 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/07 13:24:05 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"


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
	while (*tokens)
	{
		if (is_logical_operator(tokens->kind))
		{
			if (ast == NULL)
				return (false);
			ret = parse_logical_operator(tokens, ast);
		}
	}
}