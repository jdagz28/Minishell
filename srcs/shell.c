/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 13:26:05 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int shell_init(t_shell *shell, char *cmds, char **env)
{
    shell->env = strtab_cpy(env);
    shell->err = 0;
    if (!shell->env)
        return (EXIT_FAILURE);
    if (user_init(&shell->user, env) || pwd_init(&shell->pwd, env) || command_init(&shell->cmd, cmds))
    {
        shell_clear(shell);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

void shell_clear(t_shell *shell)
{
    if (shell->env)
        strtab_free(shell->env);
    user_clear(&shell->user);
    pwd_clear(&shell->pwd);
    command_clear(&shell->cmd);
}

static char *shell_cat(t_shell *shell)
{
    char *res;
    char *user;
    char *pwd;

    user = user_cat(&shell->user);
    pwd = pwd_cat(&shell->pwd);
    res = ft_strjoin(user, pwd);
    free(user);
    free(pwd);
    return (res);
}

int shell_prompt(t_shell *shell)
{
    char *cat;
    char *line;
    int err;

    cat = shell_cat(shell);
    if (!cat)
        return (EXIT_FAILURE);
    line = readline(cat);
    // leaks = still reachable : 130, 253 bytes in 191 blocks
    free(cat);
    err = user_setlastinput(&shell->user, line);
    if (!err)
        err = command_init(&shell->cmd, line);
    if (!err)
        shell->err = shell_exec_all(shell);
    command_clear(&shell->cmd);
    free(line);
    return (err);
}

int shell_exec_all(t_shell *shell)
{
    int pid;
    int status;
    int i;
    t_cmd *cmd;

    cmd = &shell->cmd;
    if (!cmd->cmd)
        return (EXIT_FAILURE);
    i = 0;
    while (i < cmd->len)
    {
        if (ft_strncmp(cmd->cmd[i][0], "exit", 4) == 0)
            clean_exit(shell, EXIT_SUCCESS);
        pid = fork();
        if (pid < 0)
            return (EXIT_FAILURE);
        if (pid == 0)
            shell_exec(cmd->cmd[i], cmd, i, shell->env);
        // ft_printf("process %d wait\n", i);
        wait(NULL);
        // ft_printf("process %d done waiting\n", i);
        i++;
    }
    pipes_close(cmd->pipes, cmd->len - 1);
    return (WEXITSTATUS(status));
}

int shell_exec(char **tab, t_cmd *cmd, int id, char **env)
{
    // ft_printf("exec cmd %d\n", id);
    if (cmd)
    {
        pipes_dup(cmd->pipes, id, cmd->len);
        pipes_close(cmd->pipes, cmd->len - 1);
        command_exec(tab, env);
    }
    return (EXIT_SUCCESS);
}
