/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/24 04:05:48 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "signal.h"
#include "execution.h"
#include "environment.h"


static int	exec_bin_error(char *cmd, char **env)
{
	char	*pwd;
	int		pwd_len;

	pwd = ft_get_env_var(env, "PWD");
	pwd_len = ft_strlen(pwd);
	if (ft_strncmp(cmd, pwd, pwd_len) == 0)
		print_error(cmd, "is a directory");
	else
		print_error(cmd, "command not found");
	return (127);
}

int	exec_bin(t_simple_cmd* cmd, char** env)
{
	char* bin;
	int		pid;
	int		status;

	signal_set(SIGINT, &write_newline);
	if (access(cmd->argv[0], F_OK) == 0)
		bin = ft_strdup(cmd->argv[0]);
	else
		bin = env_getpath(cmd->argv[0], env);
	if (!bin)
		return (exec_bin_error(cmd->argv[0], env));
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

