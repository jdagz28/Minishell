/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktab_for_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:42:08 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/25 18:51:49 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	checktab_for_var(char **tab, char *var_name)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], var_name, ft_strlen(var_name)) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}
