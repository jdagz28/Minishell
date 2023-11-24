/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 02:27:02 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 10:51:53 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

void	strtab_free(char** tab)
{
	int	i;
	int	len;

	if (!tab)
		return;
	len = strtab_len(tab);
	i = 0;
	while (i < len)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

void	strtab_freeend(char** tab, int start)
{
	int	i;
	int	len;

	if (!tab)
		return;
	len = strtab_len(tab);
	if (start >= len)
		return;
	i = start;
	while (i < len)
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
}
