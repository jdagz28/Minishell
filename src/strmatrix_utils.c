/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmatrix_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/04 14:54:46 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int strmatrix_len(char ***matrix)
{
    int i;

    i = 0;
    if (!matrix)
        return (0);
    while (matrix[i])
        i++;
    return (i);
}

char ***strtab_split(char **tab, char c)
{
    char ***res;
    int len;
    int i;

    len = strtab_len(tab);
    if (len == 0)
        return (NULL);
    res = malloc(sizeof(char **) * (len + 1));
    if (!res)
        return (NULL);
    i = 0;
    while (i < len)
    {
        res[i] = ft_split(tab[i], c);
        if (!res[i])
        {
            strmatrix_free(res);
            return (NULL);
        }
        i++;
    }
    res[i] = NULL;
    return (res);
}

void strmatrix_free(char ***matrix)
{
    int i;

    if (!matrix)
        return;
    i = 0;
    while (matrix[i])
    {
        strtab_free(matrix[i]);
        i++;
    }
    free(matrix);
}

void strmatrix_print(char ***matrix, char cesa, char cesb)
{
    int i;

    if (!matrix)
        return;
    i = 0;
    while (matrix[i])
    {
        strtab_print(matrix[i], cesb);
        ft_printf("%c", cesa);
        i++;
    }
    ft_printf("\n");
}
