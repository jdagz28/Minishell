/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getvar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:54:01 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/17 10:45:39 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_var(char **environ, const char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (environ[i] != NULL)
	{
		if (!ft_strncmp(var, environ[i], len) && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}
