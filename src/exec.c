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

/*
int exec_builtin(t_shell *shell, t_node *node)
{
}
*/
void exec_node(t_shell *shell, t_node *node)
{
    if (node->type == SIMPLE_CMD)
        exec_simple(shell, node);
    if (node->type == PIPE_NODE)
        exec_pipe(shell, node);
}

void exec_simple(t_shell *shell, t_node *node)
{
    char **cmd;
    char *bin;

    cmd = node->content.simple_cmd.argv;
    cmd = files_redirect(cmd);
    bin = env_getpath(cmd[0], shell->env);
    if (!bin)
    {
        print_error(cmd[0], "command not found");
        exit(127);
    }
    free(cmd[0]);
    cmd[0] = bin;
    execve(cmd[0], cmd, shell->env);
    exit(127);
}

static void close_pipe(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
}

void exec_pipe(t_shell *shell, t_node *node)
{
    int pid;
    int status;
    int fd[2];
    t_node *next;

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
        next = node->content.child.left;
    }
    else
    {
        waitpid(pid, &status, 0);
        dup2(fd[0], STDIN_FILENO);
        next = node->content.child.right;
    }
    close_pipe(fd);
    exec_node(shell, next);
}