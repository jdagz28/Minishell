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

int	strtab_getkey(char** tab, char* str)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (key_cmp(tab[i], str) == 0)
			return(i);
		i++;
	}
	return (-1);
}
