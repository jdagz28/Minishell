/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:54:17 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/09 12:45:01 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

const char *token_kind_strings[] = {
    "TK_WORD",
	"TK_PIPE",
	"TK_OR",
	"TK_AND",
	"TK_SEMICOLON",
	"TK_OPEN_PARENTHESIS",
	"TK_CLOSE_PARENTHESIS",
	"TK_OPERATOR",
	"TK_REDIRECT",
	"TK_EOF"
};

void	free_token(t_token *head);
void	print_tokens(t_token *tokens);
void	clear_ast(t_node **ast);

// int main(int argc, char **argv)
// {
// 	t_token		*tokens;
// 	t_node		*ast;

// 	if (argc != 2)
// 	{
// 		printf("Usage: %s script\n", argv[0]);
// 		return (1);
// 	}
// 	printf("Input: %s\n", argv[1]);
// 	tokens = tokenizer(argv[1]);
// 	print_tokens(tokens);
// 	(void)ast;
// 	if (build_ast(tokens, ast) == false)
// 	{
// 		printf("Error: building the abstract syntax tree\n");
// 		return (1);
// 	}
// 	return (0);
// }

int	main(void)
{
	t_token	*tokens;
	t_node	*ast;
	char	*line;

	ast = NULL;
	tokens = NULL;
	while (1)
	{
		line = readline("LexParser_Test> ");
		tokens = tokenizer(line);
		print_tokens(tokens);
		if (tokens)
		{
			if (build_ast(&tokens, &ast, false) == false)
			{
				if (tokens)
					printf("\nminishell: syntax error near unexpected token '%s'\n", tokens->word);
			}
		}
		// clear_ast(&ast);
		free_token(tokens);
		free(line);
	}
}

void	free_token(t_token *head)
{
	t_token	*itr;
	t_token	*next;

	if (head == NULL)
		return ;
	itr = head;
	while (itr != NULL)
	{
		next = itr->next;
		if (itr->word != NULL)
			free(itr->word);
		if (itr)
			free(itr);
		itr = next;
	}
}
void	print_tokens(t_token *tokens)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens;
	while (current != NULL)
	{
		printf("Token %d\n", i++);
		if (current->word != NULL)
			printf("Token: \t%s\n", current->word);
		printf("Type: \t%s\n\n", token_kind_strings[current->kind]);
		current = current->next;
	}
	// free_token(tokens);
}

static void	free_simple_cmd(t_node **simple_cmd)
{
	int	i;
	int	fd;

	i = 0;
	if (*simple_cmd != NULL)
	{
		i = 0;
		while ((*simple_cmd)->content.simple_cmd.argv[i] != NULL)
		{
			free((*simple_cmd)->content.simple_cmd.argv[i]);
			++i;
		}
		fd = (*simple_cmd)->content.simple_cmd.fd_input;
		if (fd > 0 && fd != STDIN_FILENO)
			close(fd);
		fd = (*simple_cmd)->content.simple_cmd.fd_output;
		if (fd > 0 && fd != STDOUT_FILENO)
			close(fd);
		free((*simple_cmd)->content.simple_cmd.argv);
		free(*simple_cmd);
	}
}

void	clear_ast(t_node **ast)
{
	if (*ast == NULL)
		return ;
	if ((*ast)->type == SIMPLE_CMD)
		free_simple_cmd(ast);
	else
	{
		clear_ast(&((*ast)->content.child.left));
		clear_ast(&((*ast)->content.child.right));
		free(ast);
	}
}
