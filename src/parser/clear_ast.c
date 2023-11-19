/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:24:15 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/16 09:33:19 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

void free_token(t_token *head)
{
	t_token *itr;
	t_token *next;

	if (head == NULL)
		return;
	itr = head;
	while (itr != NULL)
	{
		next = itr->next;
		free(itr);
		itr = next;
	}
}

static void free_simple_cmd(t_node **simple_cmd)
{
	int i;
	int fd;

	if (*simple_cmd != NULL)
	{
		i = 0;
		while ((*simple_cmd)->content.simple_cmd.argv[i] != NULL)
		{
			free((*simple_cmd)->content.simple_cmd.argv[i]);
			(*simple_cmd)->content.simple_cmd.argv[i] = NULL;
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
		*simple_cmd = NULL;
	}
}

void clear_ast(t_node **ast)
{
	if (*ast == NULL)
		return;
	if ((*ast)->type == SIMPLE_CMD)
	{
		free_simple_cmd(ast);
		*ast = NULL;
	}
	else
	{
		clear_ast(&((*ast)->content.child.left));
		clear_ast(&((*ast)->content.child.right));
		free(*ast);
		*ast = NULL;
	}
}
