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

int	strtab_add(char*** tab, char* str)
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
	if (*tab)
		free(*tab);
	*tab = res;
	return (EXIT_SUCCESS);
}
