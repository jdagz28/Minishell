/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:35:49 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/14 01:22:14 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"
#include "expansion.h"


void	expand_heredoc(t_simple_cmd *cmd)
{
	int		i;
	bool	quotes;

	i = 0;
	quotes = false;
	while (cmd->argv[i] != NULL)
	{
		if (ft_strchr(cmd->argv[i], "<<") == 0)
			quotes = (ft_strchr(cmd->argv[i + 1], '\'') != NULL
					|| ft_strchr(cmd->argv[i + 1], '"') != NULL);
		cmd->has_quotes = quotes;
		remove_quotes_arg(&cmd->argv[i]);
		i++;
	}
}

bool	expand_simplecmd(t_simple_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i] != NULL)
	{
		if (ft_strchr(cmd->argv[i], '$') != NULL \
				&& !(i > 0 && ft_strcmp(cmd->argv[i - 1], "<<") == 0))
		{
			if (expand_vars(cmd, i) == false)
				return (false);
		}
		i++;
	}
	expand_heredoc(cmd);
	return (true);
}

bool	expand_cmds(t_node *ast)
{
	if (ast->type == SIMPLE_CMD)
		if (expand_simplecmd(&ast->content.simple_cmd) == false)
			return (false);
	else
	{
		if (ast->content.child.left != NULL)
			if (expand_cmds(ast->content.child.left) == false)
				return (false);
		if (ast->content.child.right != NULL)
			if (expand_cmds(ast->content.child.right) == false)
				return (false);
	}
	return (true);
}
