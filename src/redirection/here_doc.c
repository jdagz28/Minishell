/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/30 12:36:36 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"
#include "expansion.h"
#include "strtab.h"
#include "signal.h"

static void read_here_doc(t_shell *shell, char* limiter, int fd)
{
	char* line;
	int len;

	len = ft_strlen(limiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_error("warning: here-document at line 1 delimited by end-of-file, wanted: ", limiter);
			close(fd);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(line, limiter, len) == 0)
		{
			free(line);
			break;
		}
		expand_vars_heredoc(&line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	exit(EXIT_SUCCESS);
}
int get_here_doc(t_shell *shell, t_simple_cmd *cmd, char *limiter)
{
	int pid;
	int fd[2];
	int status;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return(-1);
	if (pid == 0)
	{
		signal_set(SIGINT, &exit_newline);
		close(fd[0]);
		read_here_doc(shell, limiter, fd[1]);
	}
	cmd->fd_input = fd[0];
	close(fd[1]);
	wait(&status);
	if (WEXITSTATUS(status))
	{
		close(fd[0]);
		cmd->fd_input = -1;
	}
	return (WEXITSTATUS(status));
}


/*
int get_here_doc(char *limiter)
{
	int i;
	int fd[2];


	if (!tab || !*tab)
		return(-1);
	i = 0;
	
	if (pipe(fd) == -1)
		return(-1);
	while (tab[i])
	{
		write(fd[1], tab[i], ft_strlen(tab[i]));
		write(fd[1], "\n", 1);
		i++;
	}
	close(fd[1]);
	strtab_free(tab);
	return(fd[0]);
}*/
