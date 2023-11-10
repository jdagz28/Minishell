/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:08:42 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/10 10:38:32 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSING_H
# define LEXER_PARSING_H

typedef struct s_token	t_token;

extern const char	*token_kind_strings[]; //!tester-printing-token-type

typedef enum e_tk_kind
{
	TK_WORD,
	TK_PIPE,
	TK_OR,
	TK_AND,
	TK_SEMICOLON,
	TK_OP_PAREN,
	TK_CL_PAREN,
	TK_OPERATOR,
	TK_REDIRECT,
	TK_EOF
}	t_tk_kind;

typedef struct s_token
{
	char		*word;
	t_tk_kind	kind;
	t_token		*next;
}	t_token;

typedef enum e_node_type
{
	SIMPLE_CMD,
	PIPE_NODE,
	OR_NODE,
	AND_NODE,
	SEMICOLON_NODE
}	t_node_type;

typedef struct s_simple_cmd
{
	char	**argv;
	int		fd_input;
	int		fd_output;
	bool	has_quotes;
}	t_simple_cmd;

typedef struct s_node	t_node;

typedef struct s_child
{
	t_node	*left;
	t_node	*right;
}	t_child;

typedef union u_node_content
{
	t_simple_cmd	simple_cmd;
	t_child			child;
}	t_node_content;

typedef struct s_node
{
	t_node_type		type;
	t_node_content	content;
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

//parse_logical.c
bool	is_logical_operator(enum e_tk_kind kind);
bool	parse_logical_operator(t_token **tokens, t_node **ast, \
								bool is_subshell);

//parse_parenthesis.c
bool	parse_parenthesis(t_token **tokens, t_node **ast);

//parse_pipeline.c
bool	parse_pipeline(t_token **tokens, t_node **ast, bool is_subshell);

//parse_simple_cmd.c
bool	is_redirect_word(enum e_tk_kind kind);
bool	parse_simple_cmd(t_token **tokens, t_node **ast, bool is_subshell);

//parser_utils.c
void	consume_token(t_token **tokens);
void	clear_tokens(t_token **tokens);

//parser.c
bool	build_ast(t_token **tokens, t_node **ast, bool is_subshell);

#endif