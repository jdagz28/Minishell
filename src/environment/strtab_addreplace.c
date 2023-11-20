/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_addreplace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 02:26:35 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 02:26:56 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	strtab_replace_line(char ***tab, char *str, int id)
{
	if (id < 0)
		return (EXIT_FAILURE);
	free(*tab[id]);
	*tab[id] = str;
	return (EXIT_SUCCESS);
}

int	strtab_add_line(char ***tab, char *str)
{
	char	**res;
	int		len;

	if (!tab || !str)
		return (EXIT_FAILURE);
	len = strtab_len(*tab);
	res = malloc(sizeof(char *) * (len + 2));
	if (!res)
		return (EXIT_FAILURE);
	ft_memcpy(res, *tab, sizeof(char *) * len);
	res[len] = str;
	res[len + 1] = NULL;
	free(*tab);
	*tab = res;
	return (EXIT_SUCCESS);
}