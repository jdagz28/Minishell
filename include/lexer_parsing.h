/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:08:42 by jdagoy            #+#    #+#             */
/*   Updated: 2023/10/30 23:51:22 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSING_H
# define LEXER_PARSING_H


typedef enum e_tk_kind
{
	TK_WORD,
	TK_OPTION_COMMAND,
	TK_REDIRECT_LEFT,
	TK_REDIRECT_RIGHT,
	TK_REDIRECT_HEREDOC,
	TK_REDIRECT_APPEND,
	TK_PIPE,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE
	TK_VARIABLE,
	TK_BACKSLASH,
	TK_SEMICOLON,
	TK_LITERAL,
	TK_SPACE
	TK_EOF
}	t_tk_kind;


struct s_token
{
	char		*word;
	t_tk_kind	kind;
	t_token		*next;
}	t_token;


#endif