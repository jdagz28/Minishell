/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:35:49 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/13 14:51:25 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"


static bool	expand_singlevar(t_simple_cmd *cmd, int const i, \
								int *j, bool dou_quote)
{
	char	*var_name;
	char	*var_value;

	
}

static bool	next_char(char *c)
{
	return (c == '\0' || ((ft_isalnum(c) == 0 && c != '_') && c != '?'));
}

bool	expand_envvars(t_simple_cmd *cmd, int const i)
{
	int		j;
	bool	sin_quote;
	bool	dou_quote;

	j = 0;
	sin_quote = false;
	dou_quote = false;
	while (cmd->argv[i] != NULL && cmd->argv[i][j] != '\0')
	{
		if (cmd->argv[i][j] == '$' && sin_quote == false)
		{
			if (next_char(cmd->argv[i][j + 1]) == true)
				cmd->argv[i] = replace_varvalue(&cmd->argv[i], 0, j++, "$");
			{
				if (expand_singlevar(cmd, i, &j, dou_quote) == false)
					return (false);
			}
		}
		else
		{
			change_quote_state(cmd->argv[i][j], &sin_quote, &dou_quote);
			j++;
		}
	}
	return (true);
}

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
		remove_quotes(&cmd->argv[i]);
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
			if (expand_envvars(cmd, i) == false)
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
