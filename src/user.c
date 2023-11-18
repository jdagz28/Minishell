/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intmatrix_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 13:26:27 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int user_init(t_user *user, char **env)
{
    user->username = env_get("USER=", 0, env);
    user->machinename = env_get("SESSION_MANAGER=local/", ':', env);
    if (!user->username || !user->machinename)
    {
        user_clear(user);
        return (EXIT_FAILURE);
    }
    user->lastinput = NULL;
    return (EXIT_SUCCESS);
}

void user_clear(t_user *user)
{
    if (user->username)
        free(user->username);
    if (user->machinename)
        free(user->machinename);
    if (user->lastinput)
        free(user->lastinput);
    // rl_clear_history();
}

int user_setlastinput(t_user *user, char *str)
{
    if (str && ft_strncmp(user->lastinput, str, ft_strlen(str)) != 0)
    {
        add_history(str);
        //  leaks = still reachable: 4,054 bytes in 4 blocks
        if (user->lastinput)
            free(user->lastinput);
        user->lastinput = ft_strdup(str);
        if (!user->lastinput)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

char *user_cat(t_user *user)
{
    char *res;
    int len;

    len = ft_strlen(user->username) + ft_strlen(user->machinename) + 2;
    res = malloc(sizeof(char) * (len + 1));
    if (!res)
        return (NULL);
    ft_strlcpy(res, user->username, len + 1);
    ft_strlcat(res, "@", len + 1);
    ft_strlcat(res, user->machinename, len + 1);
    ft_strlcat(res, ":", len + 1);
    return (res);
}