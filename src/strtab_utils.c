/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/04 14:54:46 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int strtab_beginwith(char **tab, char *str)
{
    int i;
    int len;

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

void strtab_print(char **tab, char ces)
{
    int i;

    if (!tab)
        return;
    i = 0;
    while (tab[i])
    {
        ft_printf("%s%c", tab[i], ces);
        i++;
    }
}

int strtab_len(char **tab)
{
    int i;

    if (!tab)
        return (0);
    i = 0;
    while (tab[i])
        i++;
    return (i);
}

char **strtab_cpy(char **tab)
{
    char **res;
    int i;
    int len;

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

void strtab_free(char **tab)
{
    int i;
    int len;

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

void strtab_freeend(char **tab, int start)
{
    int i;
    int len;

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

int strtab_replace_line(char ***tab, char *str, int id)
{
    if (id < 0)
        return (EXIT_FAILURE);
    free(*tab[id]);
    *tab[id] = str;
    return (EXIT_SUCCESS);
}

int strtab_add_line(char ***tab, char *str)
{
    char **res;
    int len;

    if (!tab || !str)
        return (EXIT_FAILURE);
    len = strtab_len(*tab);
    res = malloc(sizeof(char *) * (len + 2));
    if (!res)
        return (EXIT_FAILURE);
    ft_memcpy(res, *tab, sizeof(char *) * len);
    res[len] = str;
    res[len + 1] = NULL;
    free(*tab);
    *tab = res;
    return (EXIT_SUCCESS);
}