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

int	strtab_replace(char** tab, char* str, int id)
{
	int len;

	if (!str)
		return(EXIT_FAILURE);
	len = strtab_len(tab);
	if (id < 0 || id >= len)
		return (EXIT_FAILURE);
	if (tab[id])
		free(tab[id]);
	tab[id] = str;
	return (EXIT_SUCCESS);
}

