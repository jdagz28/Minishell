/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:58:02 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/28 14:02:10 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "strtab.h"

static bool	expand_singlevar(t_expandvar* p, int* j, t_shell* shell)
{
	char* var_name;
	char* var_value;

	get_var_name_value(&p->cmd->argv[p->i][*j], &var_name, &var_value, shell);
	if (p->dou_quotes == false && var_value != NULL && *var_value != '\0' \
		&& has_space(var_value) == true)
	{
		if (realloc_argv(p->cmd, p->i, j, var_value) == false)
		{
			free(var_name);
			if (*var_value != '\0')
				free(var_value);
			return (false);
		}
	}
	else
	{
		p->cmd->argv[p->i] = replace_varval(&p->cmd->argv[p->i], \
			ft_strlen(var_name), *j, var_value);
		*j = *j + ft_strlen(var_value);
	}
	free(var_name);
	if (*var_value != '\0')
		free(var_value);
	return (true);
}

static void	update_command_arg(t_expandvar* params)
{
	if (params->new_word)
	{
		free(params->cmd_argv[params->i]);
		params->cmd_argv[params->i] = ft_strdup(params->new_word);
		free(params->new_word);
		params->new_word = NULL;
	}
}

static void	process_non_var(t_expandvar* params, char c)
{
	change_quote_state(c, &(params->sin_quotes), &(params->dou_quotes));
	append_char(&(params->new_word), c);
}

static bool	handle_dollar_sign(t_expandvar* params, t_shell* shell)
{
	char* temp;
	int		original_j;

	temp = &(params->cmd_argv[params->i][params->j]);
	if (params->cmd_argv[params->i][params->j] == '$')
	{
		if (next_char(params->cmd_argv[params->i][params->j + 1]) == true)
		{
			params->cmd_argv[params->i] = replace_varval(\
				& params->cmd_argv[params->i], 0, params->j++, "$");
		}
		else if (*temp == '$' && (*(temp + 1) == '\0' || \
			* (temp + 1) == '\'' || *(temp + 1) == '\"'))
		{
			append_char(&(params->new_word), *temp);
			params->j++;
		}
		else
		{
			original_j = params->j;
			return (expand_singlevar(params, &original_j, shell));
		}
	}
	return (true);
}

bool	expand_vars(t_simple_cmd* cmd, int const i, t_shell* shell)
{
	t_expandvar	p;

	init_expandvar(&p, i, cmd);
	while (p.cmd_argv[p.i] != NULL && p.cmd_argv[p.i][p.j] != '\0')
	{
		if (p.cmd_argv[p.i][p.j] == '$' && p.sin_quotes == false)
		{
			if (handle_dollar_sign(&p, shell) == false)
				return (false);
		}
		else
			process_non_var(&p, p.cmd_argv[p.i][p.j++]);
	}
	update_command_arg(&p);
	return (true);
}
