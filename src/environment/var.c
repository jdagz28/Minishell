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

int	var_replace(t_shell *shell, char *str, int id)
{
	char	*new;

	new = ft_strdup(str);
	if (!new)
		return (EXIT_FAILURE);
	free(shell->var[id]);
	shell->var[id] = new;
	return (EXIT_SUCCESS);
}

int	var_add(t_shell *shell, char *str)
{
	char	**res;
	char	*new;
	int		len;
	int		i;

	len = strtab_len(shell->var) + 1;
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (EXIT_FAILURE);
	new = ft_strdup(str);
	if (!new)
	{
		free(res);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < len)
	{
		if (i == len - 1)
			res[i] = new;
		else
			res[i] = shell->var[i];
		i++;
	}
	res[i] = NULL;
	free(shell->var);
	shell->var = res;
	return (EXIT_SUCCESS);
}

int	var_get_id(char **tab, char *str)
{
	char	*sep;
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

int	var_unset(t_shell *shell, char *str)
{
	char	**res;
	int		len;
	int		id;
	int		i;

	id = var_get_id(shell->var, str);
	if (id == -1)
		return (EXIT_SUCCESS);
	len = strtab_len(shell->var);
	if (len == 1)
	{
		strtab_free(shell->var);
		shell->var = NULL;
	}
	res = malloc(sizeof(char *) * len);
	if (!res)
		return (EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		if (i < id)
			res[i] = shell->var[i];
		if (i == id)
			free(shell->var[i]);
		if (i > id)
			res[i - 1] = shell->var[i];
		i++;
	}
	res[i] = NULL;
	free(shell->var);
	shell->var = res;
	return (EXIT_SUCCESS);
}

int	var_set(t_shell *shell, char *str)
{
	int	id;

	id = var_get_id(shell->var, str);
	if (id != -1)
		var_replace(shell, str, id);
	else
		var_add(shell, str);
	return (id);
}
