/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 13:26:05 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
static char ***command_init_cmd(char *str)
{
    char ***res;
    char **temp;

    temp = NULL;
    temp = ft_split(str, '|');
    if (!temp)
        return (NULL);
    res = strtab_split(temp, ' ');
    strtab_free(temp);
    return (res);
}

int command_init(t_cmd *cmd, char *str)
{
    if (!str)
    {
        cmd->len = 0;
        cmd->cmd = NULL;
        cmd->pipes = NULL;
        return (EXIT_SUCCESS);
    }
    cmd->cmd = command_init_cmd(str);
    if (!cmd->cmd)
        return (EXIT_FAILURE);
    cmd->len = strmatrix_len(cmd->cmd);
    cmd->pipes = pipes_init(cmd->len - 1);
    if (cmd->len > 1 && !cmd->pipes)
    {
        command_clear(cmd);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int command_clear(t_cmd *cmd)
{
    if (cmd->cmd)
    {
        strmatrix_free(cmd->cmd);
        cmd->cmd = NULL;
    }
    if (cmd->pipes)
    {
        pipes_close(cmd->pipes, cmd->len - 1);
        free(cmd->pipes);
        cmd->pipes = NULL;
    }
    return (EXIT_SUCCESS);
}
*/
/*
int command_setvar(char **cmd, t_shell *shell)
{
    int i;
    int res;
    char *addr;

    i = 0;
    res = 0;
    while (cmd[i])
    {
        addr = ft_strchr(cmd[i], '=');
        if (addr)
        {
            temp = ft_split(cmd[i], '=');
            if (!temp)
                return (EXIT_FAILURE);
            varlst_set(shell->varlst, temp[0], temp[1]);
            free(temp);
            res = 1;
        }
        i++;
    }
    return (res);
}
*/