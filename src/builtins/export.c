/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/20 10:50:50 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"
#include "builtins.h"

static char* define_str(char** tab, char* str)
{
	int		id;

	id = vartab_strpos(tab, str);
	if (id != -1)
		return (str);
	id = vartab_keypos(tab, str);
	if (id != -1)
		return (tab[id]);
	return(NULL);
}

int	export(t_shell* shell, char* str)
{
	int		id;
	char* new;
	int		err;

	if (!key_isvalid(str))
		print_error(str, "not a valid identifier");
	str = define_str(shell->var, str);
	if (!str)
		return (EXIT_FAILURE);
	new = ft_strdup(str);
	if (!new)
		return (EXIT_FAILURE);
	id = vartab_strpos(shell->env, str);
	if (id != -1)
		err = strtab_replace(shell->env, new, id);
	else
		err = strtab_add(&shell->env, new);
	if (err)
	{
		free(new);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
