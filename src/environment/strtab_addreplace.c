/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_addreplace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 02:26:35 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 10:51:40 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

int	strtab_replace_line(char*** tab, char* str, int id)
{
	if (id < 0)
		return (EXIT_FAILURE);
	free(*tab[id]);
	*tab[id] = str;
	return (EXIT_SUCCESS);
}

int	strtab_add_line(char*** tab, char* str)
{
	char** res;
	int		len;

	if (!tab || !str)
		return (EXIT_FAILURE);
	len = strtab_len(*tab);
	res = malloc(sizeof(char*) * (len + 2));
	if (!res)
		return (EXIT_FAILURE);
	ft_memcpy(res, *tab, sizeof(char*) * len);
	res[len] = str;
	res[len + 1] = NULL;
	free(*tab);
	*tab = res;
	return (EXIT_SUCCESS);
}

int	strtab_remove_line(char*** tab, int id)
{
	char** res;
	int		len;

	if (!tab)
		return (EXIT_FAILURE);
	len = strtab_len(*tab);
	if (id < 0 || id >= len)
		return(EXIT_FAILURE);
	if (len == 1)
	{
		strtab_free(*tab);
		*tab = NULL;
		return(EXIT_SUCCESS);
	}
	res = malloc(sizeof(char*) * (len));
	if (!res)
		return (EXIT_FAILURE);
	ft_memcpy(res, tab[0], sizeof(char*) * id);
	ft_memcpy(&res[id], tab[id + 1], sizeof(char*) * (len - id - 1));
	res[len - 1] = 0;
	free(*tab);
	*tab = res;
	return (EXIT_SUCCESS);
}
