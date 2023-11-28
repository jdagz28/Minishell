/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/28 00:15:03 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "environment.h"

static char	**env_get_bin_paths(char **env)
{
	char	**res;
	char	*line;

	line = env_get("PATH=", 0, env);
	if (!line)
		return (NULL);
	res = ft_split(line, ':');
	free(line);
	return (res);
}

static char	*env_trypath(char *path, char *cmd)
{
	int		len;
	char	*res;

	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	res = malloc(len * sizeof(int));
	if (!res)
		return (NULL);
	ft_strlcpy(res, path, len);
	ft_strlcat(res, "/", len);
	ft_strlcat(res, cmd, len);
	if (access(res, F_OK) == 0)
		return (res);
	free(res);
	return (NULL);
}

char	*env_getpath(char *str, char **env)
{
	int		i;
	char	*res;
	char	**paths;

	paths = env_get_bin_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		res = env_trypath(paths[i], str);
		if (res)
			break ;
		i++;
	}
	ft_splitfree(paths);
	return (res);
}
