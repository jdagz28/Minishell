/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:24:15 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/30 14:48:21 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"
#include "strtab.h"

static void	free_simple_cmd(t_node **simple_cmd)
{
	int	fd;

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

void	clear_ast(t_node **ast)
{
	if (*ast == NULL)
		return ;
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
