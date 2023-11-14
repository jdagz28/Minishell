/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:58:02 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/14 11:10:58 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

static bool	expand_singlevar(t_simple_cmd *cmd, int const i, \
								int *j, bool dou_quote)
{
	char	*var_name;
	char	*var_value;

	get_var_name_value(&cmd->argv[i][*j], &var_name, &var_value);
	if (dou_quote == false && var_value != NULL && *var_value != '\0' \
		&& has_space(var_value) == true)
	{
		if (realloc_argv(cmd, i, j, var_value) == false)
		{
			free(var_name);
			if (*var_value != '\0')
				free(var_value);
			return (false);
		}
	}
	else
	{
		cmd->argv[i] = \
			replace_varval(&cmd->argv[i], ft_strlen(var_name), *j, var_value);
		*j = *j + ft_strlen(var_value);
	}
	free(var_name);
	if (*var_value != '\0')
		free(var_value);
	return (true);
}

bool	expand_vars(t_simple_cmd *cmd, int const i)
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
				cmd->argv[i] = replace_varval(&cmd->argv[i], 0, j++, "$");
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
