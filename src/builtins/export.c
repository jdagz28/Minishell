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

int	export(t_shell* shell, char* str)
{
	int		envid;
	int		varid;
	char* new;
	int		err;

	if (!str)
		return (EXIT_FAILURE);
	varid = strtab_getkey(shell->var, str);
	if (varid == -1)
		return (EXIT_FAILURE);
	new = ft_strdup(shell->var[varid]);
	if (!new)
		return (EXIT_FAILURE);
	envid = strtab_getkey(shell->env, str);
	if (envid != -1)
		err = strtab_replace_line(&shell->env, new, envid);
	else
		err = strtab_add_line(&shell->env, new);
	if (err)
	{
		free(new);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
