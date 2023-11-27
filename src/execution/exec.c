/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 00:36:23 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/26 16:04:58 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "builtins.h"
#include "strtab.h"

static void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

static int	exec_pipe(t_shell* shell, t_node* node)
{
	int	pid;
	int	fd[2];
	int	res;

	set_is_piped(true);
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
	set_is_piped(false);
	return (res);
}

static int	exec_simple(t_shell* shell, t_node* node)
{
	t_simple_cmd* cmd;
	char** argv;
	int		err;

	cmd = &node->content.simple_cmd;
	err = redirect(cmd); // need to close fd from now
	if (err || cmd->fd_input == -1 || cmd->fd_output == -1)
		return(EXIT_FAILURE);
	argv = cmd->argv;
	if (strtab_len(argv) == 0)
		return(EXIT_SUCCESS);
	if (is_builtin(argv) == true)
		err = execute_builtin(*cmd, shell);
	else
		err = exec_bin(cmd, shell->env);
	return (err);
}

int	exec_node(t_shell* shell, t_node* node)
{
	if (node->type == SIMPLE_CMD)
		return (exec_simple(shell, node));
	if (node->type == PIPE_NODE)
		return (exec_pipe(shell, node));
	return (EXIT_SUCCESS);
}

int	shell_exec(t_shell* shell)
{
	t_node* node;
	int		pid;
	int		status;
	node = shell->ast;
	if (!node)
		return (EXIT_FAILURE);
	signal_set(SIGINT, SIG_IGN);
	if (node->type == SIMPLE_CMD)
		return(exec_simple(shell, node));
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
		exit(exec_node(shell, node));
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
