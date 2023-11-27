/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:24:15 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/28 00:20:50 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"
#include "strtab.h"

static void free_simple_cmd(t_node** simple_cmd)
{
	int fd;

	if (*simple_cmd != NULL)
	{
		strtab_free((*simple_cmd)->content.simple_cmd.argv);
		fd = (*simple_cmd)->content.simple_cmd.fd_input;
		if (fd > 0 && fd != STDIN_FILENO)
			close(fd);
		fd = (*simple_cmd)->content.simple_cmd.fd_output;
		if (fd > 0 && fd != STDOUT_FILENO)
			close(fd);
		free(*simple_cmd);
		*simple_cmd = NULL;
	}
}

void clear_ast(t_node** ast)
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
