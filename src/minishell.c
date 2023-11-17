/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 13:26:05 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int run(t_shell *shell)
{
    signal_unset(SIGINT);
    while (1)
        shell->err = shell_prompt(shell);
    return (EXIT_SUCCESS);
}

int main(int argc, char **argv, char **env)
{
    t_shell shell;
    char *cmds;
    int err;

    if (argc == 1)
        cmds = NULL;
    else
        cmds = argv[1];
    if (shell_init(&shell, cmds, env))
        return (EXIT_FAILURE);
    if (cmds)
        err = shell_exec(&shell);
    else
        run(&shell);
    shell_clear(&shell);
    return (err);
}