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
    shell->var = NULL;
    if (!shell->env)
        return (EXIT_FAILURE);
    shell->ast = parse(cmds);
    if (cmds && !shell->ast)
        return (EXIT_FAILURE);
    if (user_init(&shell->user, env) || pwd_init(&shell->pwd, env))
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

int shell_run(t_shell *shell)
{
    signal_set(SIGQUIT, SIG_IGN);
    var_set(shell, "toto=1");
    export(shell, "tot");
    while (shell->err != 128)
        shell->err = shell_prompt(shell);
    ft_printf("exit\n");
    return (128);
}

static char *shell_readline(t_shell *shell)
{
    char *cat;
    char *line;

    cat = shell_cat(shell);
    if (!cat)
        return (NULL);
    signal_set(SIGINT, &prompt_interrupt);
    line = readline(cat);
    signal_set(SIGINT, &write_newline);
    // leaks = still reachable : 130, 253 bytes in 191 blocks
    free(cat);
    if (!line)
    {
        write(1, "exit\n", 5);
        exit(128);
    }
    user_setlastinput(&shell->user, line);
    return (line);
}

int shell_prompt(t_shell *shell)
{
    char *line;
    int err;

    line = shell_readline(shell);
    shell->ast = parse(line);
    free(line);
    if (!shell->ast)
        return (EXIT_FAILURE);
    err = shell_exec(shell);
    clear_ast(&shell->ast);
    return (err);
}

int shell_exec(t_shell *shell)
{
    t_node *node;
    int pid;
    int status;

    node = shell->ast;
    if (!node)
        return (EXIT_FAILURE);
    signal_set(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == -1)
        return (EXIT_FAILURE);
    if (pid == 0)
        exit(exec_node(shell, node));
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}
