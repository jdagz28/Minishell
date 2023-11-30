/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/30 14:48:32 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

static int	var_set_one(t_shell *shell, char *str)
{
	int		id;
	char	*new;
	int		err;

	if (ft_strchr(str, '=') == NULL)
		return (EXIT_FAILURE);
	if (!key_isvalid(str))
	{
		print_error(str, "not a valid identifier");
		return (EXIT_FAILURE);
	}
	new = ft_strdup(str);
	if (!new)
		return (EXIT_FAILURE);
	id = vartab_strpos(shell->var, str);
	if (id != -1)
		err = strtab_replace(shell->var, new, id);
	else
		err = strtab_add(&shell->var, new);
	if (err)
	{
		free(new);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	var_set(t_shell *shell, char **cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return (EXIT_FAILURE);
	i = 0;
	while (cmd[i] && var_set_one(shell, cmd[i]) == EXIT_SUCCESS)
		i++;
	return (i);
}
