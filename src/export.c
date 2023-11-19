/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 13:26:05 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int export(t_shell *shell, char *str)
{
    int envid;
    int varid;
    char *new;
    int err;

    if (!str)
        return (EXIT_FAILURE);
    varid = strtab_beginwith(shell->var, str);
    if (varid == -1)
        return (EXIT_FAILURE);
    new = ft_strdup(shell->var[varid]);
    if (!new)
        return (EXIT_FAILURE);
    envid = strtab_beginwith(shell->env, str);
    if (envid != -1)
        err = strtab_replace_line(&shell->env, new, envid);
    else
        err = strtab_add_line(&shell->env, new);
    if (err)
    {
        free(new);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}