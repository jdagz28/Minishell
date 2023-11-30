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

int	vartab_set(char ***tab, char *str)
{
	int		id;
	char	*new;
	int		err;

	new = ft_strdup(str);
	if (!new)
		return (EXIT_FAILURE);
	id = vartab_strpos(*tab, str);
	if (id != -1)
		err = strtab_replace(*tab, new, id);
	else
		err = strtab_add(tab, new);
	return (err);
}

int	vartab_unset(char ***tab, char *str)
{
	int		id;

	id = vartab_keypos(*tab, str);
	if (id == -1)
		return (EXIT_SUCCESS);
	return (strtab_remove(tab, id));
}
