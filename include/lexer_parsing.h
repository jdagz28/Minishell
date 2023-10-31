/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:08:42 by jdagoy            #+#    #+#             */
/*   Updated: 2023/10/31 01:31:10 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSING_H
# define LEXER_PARSING_H

typedef struct s_token	t_token;

typedef enum e_tk_kind
{
	TK_OPERATOR,
	TK_REDIRECT,
	TK_WORD,
	TK_OPTION_COMMAND,
	TK_REDIRECT_LEFT,
	TK_REDIRECT_RIGHT,
	TK_REDIRECT_HEREDOC,
	TK_REDIRECT_APPEND,
	TK_PIPE,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE,
	TK_VARIABLE,
	TK_BACKSLASH,
	TK_SEMICOLON,
	TK_LITERAL,
	TK_EOF
}	t_tk_kind;


typedef struct s_token
{
	char		*word;
	t_tk_kind	kind;
	t_token		*next;
}	t_token;


#endif