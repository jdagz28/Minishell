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
    pwd->home = NULL;
    if (!pwd->root)
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

    len = ft_strlen(pwd->root) + 2;
    res = malloc(sizeof(char) * (len + 1));
    if (!res)
        return (NULL);
    ft_strlcpy(res, pwd->root, len + 1);
    ft_strlcat(res, "$ ", len + 1);
    return (res);
}