/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/20 00:22:46 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pwd_init(t_pwd *pwd, char **env)
{
	pwd->root = env_get("PWD=", 0, env);
	pwd->home = env_get("HOME=", 0, env);
	if (!pwd->root || !pwd->home)
	{
		pwd_clear(pwd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	pwd_clear(t_pwd *pwd)
{
	if (pwd->root)
		free(pwd->root);
	if (pwd->home)
		free(pwd->home);
}

char	*pwd_cat(t_pwd *pwd)
{
	char	*res;
	char	*str;
	int		len;
	int		home;

	len = ft_strlen(pwd->home);
	home = 0;
	if (strncmp(pwd->home, pwd->root, len) == 0)
		home = 1;
	str = &pwd->root[len * home];
	len = ft_strlen(str) + ft_strlen("$ ") + home + 1;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	ft_memset(res, 0, len);
	if (home)
		res[0] = '~';
	ft_strlcat(res, str, len);
	ft_strlcat(res, "$ ", len);
	return (res);
}
