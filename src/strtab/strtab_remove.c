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

int	strtab_remove(char*** tab, int id)
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
	ft_memcpy(&res[id], &tab[0][id + 1], sizeof(char*) * (len - id - 1));
	res[len - 1] = 0;
	free(*tab);
	*tab = res;
	return (EXIT_SUCCESS);
}

int	strtab_remove_mult(char*** tab, int id, int len)
{
	int i;
	int err;

	i = 0;
	while (i < len)
	{
		err = strtab_remove(tab, id);
		if (err == EXIT_FAILURE)
			return(err);
		i++;
	}
	return (EXIT_SUCCESS);
}
