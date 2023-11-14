/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 02:59:10 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/14 13:18:16 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"
#include "expansion.h"

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
	"TK_EOF"};

void	free_token(t_token *head);
void	clear_ast(t_node **ast);
void	print_tokens(t_token *tokens);

int main(void)
{
	t_token	*tokens;
	t_node	*ast;
	char	*line;

	setenv("hello", "Hello, world!", 1);
	
	line = "echo $hello";
	printf("var: %s\n", getenv("hello"));
	tokens = tokenizer(line);
	if (check_tokens(tokens) == false || check_wordtokens(tokens) == false)
	{
		free_token(tokens);
		// continue ;
	}
	print_tokens(tokens);
	if (build_ast(&tokens, &ast) == false)
		if (tokens)
			printf("\nminishell: syntax error near unexpected token '%s'\n", \
					tokens->word);
	printf("Before expansion: ");
	for (int i = 0; ast->content.simple_cmd.argv[i] != NULL; i++)
		printf("%s", ast->content.simple_cmd.argv[i]);
	printf("\n");
	if (expand_cmds(ast) == false)
	{
		printf("Error in expansion\n");
	}
	printf("After expansion: ");
	for (int i = 0; ast->content.simple_cmd.argv[i] != NULL; i++)
		printf("%s", ast->content.simple_cmd.argv[i]);
	printf("\n");
	clear_ast(&ast);
	free_token(tokens);
}


void	free_token(t_token *head)
{
	t_token	*itr;
	t_token	*next;

	if (head == NULL)
		return ;
	itr = head;
	next = itr->next;
	while (next != NULL)
	{
		free(itr->word);
		free(itr);
		itr = next;
		next = itr->next;
	}
	free(itr->word);
	free(itr);
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
		free(*ast);
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