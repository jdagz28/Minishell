/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:54:17 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/16 09:33:06 by jdagoy           ###   ########.fr       */
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
	"TK_EOF"};

const char *node_type_strings[] = {
	"SIMPLE_CMD",
	"PIPE_NODE",
	"OR_NODE",
	"AND_NODE",
	"SEMICOLON_NODE"};

void	print_tokens(t_token *tokens);
void	print_ast_recursive(t_node *node);
void	print_ast_dot(t_node *node, FILE *output);

void	create_dotfile(t_node *ast, int cmd_index)
{
	FILE	*dotFile;
	char	filename[50];

	snprintf(filename, sizeof(filename), "dotfiles/ast_%d.dot", cmd_index);
	dotFile = fopen(filename, "w");
	if (dotFile == NULL)
	{
		printf("Error: cannot create dot file\n");
		return ;
	}
	fprintf(dotFile, "digraph AST {\n");
	print_ast_dot(ast, dotFile);
	fprintf(dotFile, "}\n");
	fclose(dotFile);
}


int	main(void)
{
	t_token		*tokens;
	t_node		*ast;
	char		*line;
	int			cmd_index;

	ast = NULL;
	tokens = NULL;
	cmd_index = 1;
	while (1)
	{
		line = readline("LexParser_Test> ");
		tokens = tokenizer(line);
		print_tokens(tokens);
		if (check_tokens(tokens) == false || check_wordtokens(tokens) == false)
		{
			free_token(tokens);
			continue ;
		}
		if (build_ast(&tokens, &ast) == false)
			if (tokens)
				printf("\nminishell: syntax error near unexpected token '%s'\n",
					   tokens->word);
		// create_dotfile(ast, cmd_index);
		if (ast != NULL)
			clear_ast(&ast);
		clear_tokens(tokens);
		free(line);
		cmd_index++;
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
}

void	print_ast_recursive(t_node *node)
{
	if (node == NULL)
	{
		return ;
	}

	if (node->type == SIMPLE_CMD)
	{
		printf("Simple Command: ");
		for (char **arg = node->content.simple_cmd.argv; *arg != NULL; ++arg)
		{
			printf("%s ", *arg);
		}
		printf("\n");
	}
	else
	{
		printf("Node Type: %s\n", node_type_strings[node->type]);
		printf("Left Child:\n");
		print_ast_recursive(node->content.child.left);
		printf("Right Child:\n");
		print_ast_recursive(node->content.child.right);
	}
}

void print_ast_dot(t_node *node, FILE *output)
{
	if (node == NULL)
		return ;
	fprintf(output, "  node%p [label=\"", (void *)node);
	if (node->type == SIMPLE_CMD)
	{
		fprintf(output, "Simple Command: ");
		for (char **arg = node->content.simple_cmd.argv; *arg != NULL; ++arg)
		{
			fprintf(output, "%s ", *arg);
		}
	}
	else
		fprintf(output, "Node Type: %s", node_type_strings[node->type]);
	fprintf(output, "\"];\n");
	if (node->type != SIMPLE_CMD)
	{
		if (node->content.child.left)
		{
			print_ast_dot(node->content.child.left, output);
			fprintf(output, "  node%p -> node%p [label=\"Left\"];\n", (void *)node, (void *)(node->content.child.left));
		}
		if (node->content.child.right)
		{
			print_ast_dot(node->content.child.right, output);
			fprintf(output, "  node%p -> node%p [label=\"Right\"];\n", (void *)node, (void *)(node->content.child.right));
		}
	}
}

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