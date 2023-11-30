/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/30 14:49:43 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"
#include "lexer_parsing.h"
#include "builtins.h"

void	close_redirect(t_simple_cmd *cmd)
{
	if (cmd->fd_input != -1 && cmd->fd_input != 0)
		close(cmd->fd_input);
	if (cmd->fd_output != -1 && cmd->fd_output != 1)
		close(cmd->fd_output);
}

int	redirect(t_node *node, t_shell *shell)
{
	if (node->type == SIMPLE_CMD)
	{
		return (open_redirections(&node->content.simple_cmd, shell));
	}
	else
	{
		if (node->content.child.left != NULL)
			if (redirect(node->content.child.left, shell) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		if (node->content.child.right != NULL)
			if (redirect(node->content.child.right, shell) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
}
