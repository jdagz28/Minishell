/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 00:36:23 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 00:37:52 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_shell *shell, t_node *node)
{
	int	pid;
	int	fd[2];
	int	res;

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

int	exec_simple(t_shell *shell, t_node *node)
{
	char	***cmd;
	int		err;

	cmd = &node->content.simple_cmd.argv;
	*cmd = files_redirect(*cmd);
	if (is_builtin(*cmd == true))
		err = exec_builtin(shell, *cmd);
	else
		err = exec_bin(&node->content.simple_cmd, shell->env);
	return (err);
}

int	exec_node(t_shell *shell, t_node *node)
{
	if (node->type == SIMPLE_CMD)
		return (exec_simple(shell, node));
	if (node->type == PIPE_NODE)
		return (exec_pipe(shell, node));
	return (EXIT_SUCCESS);
}

int	shell_exec(t_shell *shell)
{
	t_node	*node;
	int		pid;
	int		status;

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