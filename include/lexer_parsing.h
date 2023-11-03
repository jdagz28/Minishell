/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:08:42 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/03 12:40:04 by jdagoy           ###   ########.fr       */
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
	// TK_OPTION_COMMAND,
	// TK_REDIRECT_LEFT,
	// TK_REDIRECT_RIGHT,
	// TK_REDIRECT_HEREDOC,
	// TK_REDIRECT_APPEND,
	// TK_PIPE,
	// TK_SINGLE_QUOTE,
	// TK_DOUBLE_QUOTE,
	// TK_VARIABLE,
	// TK_BACKSLASH,
	// TK_SEMICOLON,
	// TK_LITERAL,
	// TK_EOF
}	t_tk_kind;

typedef struct s_token
{
	char		*word;
	t_tk_kind	kind;
	t_token		*next;
}	t_token;

//check_word_tokens.c
bool	check_wordtokens(t_token *token);

//check_opred_tokens.c
bool	check_tokens(t_token *tokens);

//check_token.c
bool	is_operator(char *line);
bool	is_redirect(char *line);
bool	is_metacharacter(char c);

//create_token.c
t_token	*operator_token(char **remaining, char *line);
t_token	*redirect_token(char **remaining, char *line);
t_token	*word_token(char **remaining, char *line);

//tokenizer.c
t_token	*tokenizer(char *input);

//tokenizer_utils.c
bool	check_whitespace(char **next_inline, char *line);
bool	startswith(char *line, char *prefix);
void	tk_error_manager(char *error_msg);
void	check_missingquotes(char **line, bool *flag, char quote_type);

#endif