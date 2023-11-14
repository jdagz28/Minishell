/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace_var_value.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:36:42 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/14 00:10:39 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

static char	*alloc_new_arg(char *argv, int len_varname, char *var_value)
{
	char	*new_argv;
	int		len_varvalue;

	len_varvalue = ft_strlen(var_value);
	new_argv = ft_calloc(ft_strlen(argv) - len_varname + len_varvalue, \
					sizeof(*new_argv));
	return (new_argv);
}

char	*replace_varval(char **argv, int len_varname, int i, char *var_value)
{
	int		j;
	int		k;
	char	*new_arg;

	j = 0;
	new_arg = alloc_new_arg(*argv, len_varname, var_value);
	while (j < i)
	{
		new_arg[j] = (*argv)[j];
		j++;
	}
	k = 0;
	while (var_value[k])
		new_arg[j++] = var_value[k++];
	i = i + len_varname + 1;
	while ((*argv)[i] != '\0')
		new_arg[j++] = (*argv)[i++];
	new_arg[j] = '\0';
	free(*argv);
	return (new_arg);
}
