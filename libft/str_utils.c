/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/04 14:54:46 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_strndup(char *str, int len)
{
    int strlen;
    char *res;

    if (!str || len == 0)
        return (NULL);
    strlen = ft_strlen(str);
    if (len > strlen)
        len = strlen;
    res = malloc(sizeof(char) * (len + 1));
    if (!res)
        return (NULL);
    ft_strlcpy(res, str, len);
    return (res);
}