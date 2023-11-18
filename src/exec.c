/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 13:26:05 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int exec_node(t_shell *shell, t_node *node)
{
    signal_set(SIGINT, SIG_IGN);
    if (node->type == SIMPLE_CMD)
        return (exec_simple(shell, node));
    if (node->type == PIPE_NODE)
        return (exec_pipe(shell, node));
    return (EXIT_SUCCESS);
}

int exec_simple(t_shell *shell, t_node *node)
{
    char **cmd;
    int err;
    int pid;
    int status;

    pid = fork();
    if (pid == -1)
        return (EXIT_FAILURE);
    if (pid == 0)
    {
        cmd = node->content.simple_cmd.argv;
        cmd = files_redirect(cmd);
        err = exec_builtin(shell, cmd);
        if (err)
            exit(err);
        exec_bin(cmd, shell->env);
    }
    waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}

int exec_builtin(t_shell *shell, char **cmd)
{
    if (ft_strncmp(cmd[0], "exit", 4) == 0)
        exit(128);
    if (ft_strncmp(cmd[0], "pwd", 3) == 0)
    {
        ft_printf("%s\n", shell->pwd.root);
        return (1);
    }
    return (0);
}

void exec_bin(char **cmd, char **env)
{
    char *bin;

    bin = env_getpath(cmd[0], env);
    if (!bin)
    {
        print_error(cmd[0], "command not found");
        exit(127);
    }
    free(cmd[0]);
    cmd[0] = bin;
    execve(cmd[0], cmd, env);
    exit(127);
}

static void close_pipe(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
}

int exec_pipe(t_shell *shell, t_node *node)
{
    int pid;
    int fd[2];
    int res;

    if (pipe(fd) < 0)
        exit(EXIT_FAILURE);
    pid = fork();
    if (pid == -1)
    {
        close_pipe(fd);
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close_pipe(fd);
        exit(exec_node(shell, node->content.child.left));
    }
    dup2(fd[0], STDIN_FILENO);
    close_pipe(fd);
    res = exec_node(shell, node->content.child.right);
    waitpid(pid, NULL, 0);
    return (res);
}