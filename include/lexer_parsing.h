/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:08:42 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/07 13:32:30 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSING_H
# define LEXER_PARSING_H

typedef struct s_token	t_token;

extern const char	*token_kind_strings[];

typedef enum e_tk_kind
{
	TK_OPERATOR,
	TK_REDIRECT,
	TK_WORD,
	TK_SEMICOLON,
	TK_OR,
	TK_AND,
	TK_PIPE,
	TK_EOF
}	t_tk_kind;

typedef struct s_token
{
	char		*word;
	t_tk_kind	kind;
	t_token		*next;
}	t_token;


typedef struct s_child
{
	struct s_node	*left;
	struct s_node	*right;
}	t_child;

typedef union u_node_content
{
	struct s_simple_cmd simple_cmd;
	struct s_child		child;
}	t_node_content;

typedef struct s_node
{
	enum e_node_type	type;
	t_node_content		content;
}	t_node;

//check_word_inquote.c
bool	check_word_inquote(char **word);

//check_word_tokens.c
bool	check_wordtokens(t_token *token);

//check_opred_tokens.c
bool	check_tokens(t_token *tokens);

//check_token.c
bool	is_operator(char *line);
bool	is_redirect(char *line);
bool	is_metacharacter(char c);
bool	is_word(char *line);

//create_token.c
t_token	*operator_token(char **remaining, char *line);
t_token	*redirect_token(char **remaining, char *line);
t_token	*word_token(char **remaining, char *line);
t_token	*create_token(char *word, t_tk_kind kind);

//tokenizer.c
t_token	*tokenizer(char *input);

//tokenizer_utils.c
bool	check_whitespace(char **next_inline, char *line);
bool	check_prefix(char *line, char *prefix);
void	tk_error_manager(char *error_msg);
void	check_missingquotes(char **line, bool *flag, char quote_type);

#endif