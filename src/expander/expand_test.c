/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 02:59:10 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/14 11:14:03 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"
#include "expansion.h"

void	free_token(t_token *head);
void	clear_ast(t_node **ast);

int main(void)
{
	t_token	*tokens;
	t_node	*ast;
	char	*line;

	setenv("hello", "Hello, world!", 1);
	
	line = "echo $hello";
	tokens = tokenizer(line);
	if (check_tokens(tokens) == false || check_wordtokens(tokens) == false)
	{
		free_token(tokens);
		// continue ;
	}
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
	if (ast != NULL)
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
	while (itr != NULL)
	{
		next = itr->next;
		if (itr->word)
			free(itr->word);
		free(itr);
		itr = next;
	}
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