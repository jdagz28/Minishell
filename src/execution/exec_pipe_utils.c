/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:10:30 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/30 15:12:21 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "builtins.h"
#include "strtab.h"

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	child_process(int fd[2], t_shell *shell, t_node *node)
{
	dup2(fd[1], STDOUT_FILENO);
	close_pipe(fd);
	close_redirect(&node->content.simple_cmd);
	exit(exec_node(shell, node->content.child.left));
}

void	parent_process(int fd[2], t_shell *shell, t_node *node, int *res)
{
	dup2(fd[0], STDIN_FILENO);
	close_pipe(fd);
	close_redirect(&node->content.simple_cmd);
	res = exec_node(shell, node->content.child.right);
}

void	duplicate_restore_fds(int *original_stdin, \
									int *original_stdout, int mode)
{
	if (mode == 0)
	{
		original_stdin = dup(STDIN_FILENO);
		original_stdout = dup (STDOUT_FILENO);
	}
	else if (mode == 1)
	{
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdin);
		close(original_stdout);
	}
}

void	end_parent(int pid, int *original_stdin, int *original_stdout)
{
	waitpid(pid, NULL, 0);
	duplicate_restore_fds(original_stdin, original_stdout, 1);
	set_is_piped(false);
}
