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
    shell->varlst = NULL;
    if (!shell->env)
        return (EXIT_FAILURE);
    shell->ast = parse(cmds);
    if (cmds && !shell->ast)
        return (EXIT_FAILURE);
    if (user_init(&shell->user, env) || pwd_init(&shell->pwd, env)) // || command_init(&shell->cmd, cmds))
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
    if (shell->ast)
        clear_ast(&shell->ast);
    user_clear(&shell->user);
    pwd_clear(&shell->pwd);
    // command_clear(&shell->cmd);
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
    if (!line)
        return (EXIT_SUCCESS);
    err = user_setlastinput(&shell->user, line);
    shell->ast = parse(line);
    free(line);
    if (!shell->ast)
        return (EXIT_FAILURE);
    if (!err)
        //    print_ast_recursive(shell->ast);
        err = shell_exec(shell);
    clear_ast(&shell->ast);
    return (err);
}

int shell_exec(t_shell *shell)
{
    int pid;
    int status;
    int argv_inc;
    char ***cmd;
    t_node *node;

    node = shell->ast;
    if (!node)
        return (EXIT_FAILURE);
    if (node->type == SIMPLE_CMD)
    {
        argv_inc = var_unset(shell, node);
        var_inject(shell, node);
        argv_inc += var_extract(shell, node);
        // exec_builtin(shell, node);
    }
    else
        argv_inc = 0;
    pid = fork();
    if (pid == -1)
        return (EXIT_FAILURE);
    if (pid == 0)
    {
        cmd = &node->content.simple_cmd.argv;
        *cmd = cmd[argv_inc];
        exec_node(shell, shell->ast);
    }
    waitpid(pid, &status, 0);
    return (status);
}
