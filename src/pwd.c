/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 13:26:05 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int pwd_init(t_pwd *pwd, char **env)
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

void pwd_clear(t_pwd *pwd)
{
    if (pwd->root)
        free(pwd->root);
    if (pwd->home)
        free(pwd->home);
}

char *pwd_cat(t_pwd *pwd)
{
    char *res;
    int len;
    char *str;
    int home;

    len = ft_strlen(pwd->home);
    home = 0;
    if (strncmp(pwd->home, pwd->root, len) == 0)
        home = 1;
    str = &pwd->root[len * home];
    len = ft_strlen(str) + ft_strlen("$ ") + home;
    res = malloc(sizeof(char) * (len + 1));
    if (!res)
        return (NULL);
    if (home)
        res[0] = '~';
    ft_strlcat(res, str, len + 1);
    ft_strlcat(res, "$ ", len + 1);
    return (res);
}