/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/20 11:01:25 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int key_cmp(char* line, char* needle)
{
	size_t len;

	if (!line || !needle)
		return(EXIT_FAILURE);
	len = ft_strlen(needle);
	if (ft_strncmp(line, needle, len) != 0)
		return (EXIT_FAILURE);
	if (ft_strlen(line) <= len)
		return (EXIT_FAILURE);
	if (line[len] != '=')
		return(EXIT_FAILURE);
	return(EXIT_SUCCESS);
}

int	vartab_pos(char** tab, char* str)
{
	int	i;

	if (!tab)
		return(-1);
	i = 0;
	while (tab[i])
	{
		if (key_cmp(tab[i], str) == 0)
			return(i);
		i++;
	}
	return (-1);
}

int	vartab_keypos(char** tab, char* str)
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
