/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/20 00:37:11 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exec_bin(t_simple_cmd *cmd, char **env)
{
	char	*bin;
	int		pid;
	int		status;

	signal_set(SIGINT, &write_newline);
	bin = env_getpath(cmd->argv[0], env);
	if (!bin)
	{
		print_error(cmd->argv[0], "command not found");
		exit(127);
	}
	free(cmd->argv[0]);
	cmd->argv[0] = bin;
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		execve(cmd->argv[0], cmd->argv, env);
		exit(127);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

static void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}
