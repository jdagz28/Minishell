/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/13 21:08:55 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"
#include "builtins.h"

static int	var_extract_id(char** tab, char* str)
{
	char* sep;
	int		len;
	int		i;

	sep = ft_strchr(str, '=');
	if (!sep)
		return (-1);
	len = sep - str;
	i = 0;
	while (tab && tab[i])
	{
		if (ft_strncmp(tab[i], str, len + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	var_unset(t_shell* shell, char* str)
{
	int		id;

	id = strtab_getkey(shell->var, str);
	if (id == -1)
		return (EXIT_SUCCESS);
	return(strtab_remove_line(&shell->var, id));
}

int	var_set(t_shell* shell, char* str)
{
	int	id;
	char* new;
	int err;

	new = ft_strdup(str);
	if (!new)
		return(EXIT_FAILURE);
	id = var_extract_id(shell->var, str);
	if (id != -1)
		err = strtab_replace_line(&shell->var, str, id);
	else
		err = strtab_add_line(&shell->var, new);
	return (err);
}
