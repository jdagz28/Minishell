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

void pipes_close(int (*pipes)[2], int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}

int (*pipes_init(int len))[2]
{
    int(*res)[2];
    int i;

    if (len < 1)
        return (NULL);
    res = (int(*)[2])malloc(len * sizeof(int[2]));
    if (!res)
        return (NULL);
    i = 0;
    while (i < len)
    {
        if (pipe(res[i]) == -1)
        {
            pipes_close(res, i);
            free(res);
            return (NULL);
        }
        i++;
    }
    return (res);
}

void pipes_dup(int (*pipes)[2], int id, int len)
{
    if (id > 0)
    {
        // ft_printf("process : %d dup STDIN to pipe %d\n", id, id - 1);
        dup2(pipes[id - 1][0], STDIN_FILENO);
    }
    if (len > id + 1)
    {
        // ft_printf("process : %d dup STDOUT to pipe %d\n", id, id);
        dup2(pipes[id][1], STDOUT_FILENO);
    }
}