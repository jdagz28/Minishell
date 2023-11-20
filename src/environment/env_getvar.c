/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getvar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 22:54:01 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 10:59:43 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

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

char	*env_get(char *start, char end, char **env)
{
	char	*res;
	char	*line;
	int		len;
	int		id;

	id = strtab_beginwith(env, start);
	if (id == -1)
		return (NULL);
	line = env[id];
	line = &line[ft_strlen(start)];
	len = ft_strchr(line, end) - line;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, line, len + 1);
	return (res);
}
