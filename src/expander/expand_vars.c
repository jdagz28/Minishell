/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:58:02 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/21 01:38:19 by jdagoy           ###   ########.fr       */
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

static void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = malloc(size);
	// if (new == NULL)
	// 	fatal_error("malloc");
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}


static void	update_command_arg(char **cmd_argv, int i, char *new_word)
{
	if (new_word)
	{	
		free(cmd_argv[i]);
		cmd_argv[i] = ft_strdup(new_word);
		free(new_word);
	}
}

static void	process_non_var(char **new_word, char c, bool *sin_quotes, \
								bool *dou_quotes)
{
	change_quote_state(c, sin_quotes, dou_quotes);
	append_char(new_word, c);
}

static int	handle_dollar_sign(char **cmd_argv, int *j, char **new_word, \
				bool sin_quotes)
{
	char *temp;

	temp = &(*cmd_argv)[*j];
	if ((*cmd_argv)[*j] == '$' && sin_quotes == false)
	{
		if (next_char((*cmd_argv)[*j + 1]) == true)
			*cmd_argv = replace_varval(cmd_argv, 0, (*j)++, "$");
		else if (*temp == '$' && (*(temp + 1) == '\0' || *(temp + 1) == '\'' \
					|| *(temp + 1) == '\"')) 
		{
			printf("Appending dollar sign: %c\n", *temp);
			append_char(new_word, *temp);
			(*j)++;
		}
	}
	return (true);
}

bool	expand_vars(t_simple_cmd *cmd, int const i)
{
	int		j;
	bool	sin_quote;
	bool	dou_quote;
	char	*new_word;

	j = 0;
	new_word = NULL;
	sin_quote = false;
	dou_quote = false;
	while (cmd->argv[i] != NULL && cmd->argv[i][j] != '\0')
	{
		if (cmd->argv[i][j] == '$' && sin_quote == false)
		{
			if (!handle_dollar_sign(&cmd->argv[i], &j, &new_word, \
										sin_quote))
				return (false);
			else 
				return(expand_singlevar(cmd, i, &j, dou_quote));
		}
		else
			process_non_var(&new_word, cmd->argv[i][j++], &sin_quote, \
									&dou_quote);
	}
	update_command_arg(cmd->argv, i, new_word);
	return (true);
}
