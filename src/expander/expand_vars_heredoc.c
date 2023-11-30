/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:02:21 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/30 11:38:30 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "strtab.h"

static void	heredoc_singlevar(char	**expanded_arg, int *index, t_shell *shell)
{
	char	*var_name;
	char	*var_value;

	get_var_name_value(*expanded_arg + *index, &var_name, &var_value, shell);
	*expanded_arg = replace_varval(expanded_arg, \
						ft_strlen(var_name), *index, var_value);
	*index += ft_strlen(var_value);
	free(var_name);
	if (*var_value != '\0')
		free(var_value);
}


void	expand_vars_heredoc(char **argv, t_shell *shell)
{
	int		i;
	char	*expanded_arg;

	
		i = 0;
		expanded_arg = ft_strdup(*argv);
		while (i < (int)ft_strlen(expanded_arg))
		{
			while (ft_isspace(expanded_arg[i]) || expanded_arg[i] == '\"' \
						|| expanded_arg[i] == '\'')
				i++;
			if (expanded_arg[i] == '$')
				heredoc_singlevar(&expanded_arg, &i, shell);
			else
				i++;
		}
		free(*argv);
		*argv = expanded_arg;
}
