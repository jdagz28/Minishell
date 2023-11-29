/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 00:36:23 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/29 00:56:40 by jdagoy           ###   ########.fr       */
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
	int original_stdin;
	int original_stdout;
	
	set_is_piped(true);
	res = redirect(node, shell); // need to close fd from now
	if (res || node->content.simple_cmd.fd_input == -1 || node->content.simple_cmd.fd_output == -1)
		return(EXIT_FAILURE);
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup (STDOUT_FILENO);
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
		close_redirect(&node->content.simple_cmd);
		exit(exec_node(shell, node->content.child.left));
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close_pipe(fd);
		close_redirect(&node->content.simple_cmd);
		res = exec_node(shell, node->content.child.right);
		waitpid(pid, NULL, 0);
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
	}
	set_is_piped(false);
	return (res);
}

static int	exec_simple(t_shell* shell, t_node* node)
{
	t_simple_cmd* cmd;
	char** argv;
	int		err;

	cmd = &node->content.simple_cmd;
	err = redirect(node, shell); // need to close fd from now
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
