/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/20 10:52:09 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"

int	strtab_beginwith(char **tab, char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], str, len) == 0)
		{
			if ((int)ft_strlen(tab[i]) > len)
				return (i);
		}
		i++;
	}
	return (-1);
}

void	strtab_print(char **tab, char ces)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		ft_printf("%s%c", tab[i], ces);
		i++;
	}
}

int	strtab_len(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**strtab_cpy(char **tab)
{
	char	**res;
	int		i;
	int		len;

	len = strtab_len(tab);
	if (len == 0)
		return (NULL);
	res = malloc(sizeof(char **) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		res[i] = ft_strdup(tab[i]);
		if (!res[i])
		{
			strtab_free(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
