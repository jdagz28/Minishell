/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/28 16:23:40 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"
#include "expansion.h"
#include "strtab.h"

char** read_here_doc(char* limiter)
{
	char** res;
	char* line;
	int len;
	int err;

	res = NULL;
	len = ft_strlen(limiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_error("warning: here-document at line 1 delimited by end-of-file, wanted: ", limiter);
			strtab_free(res);
			return(NULL);
		}
		if (ft_strncmp(line, limiter, len) == 0)
		{
			free(line);
			break;
		}
		err = strtab_add(&res, line);
		if (err)
		{
			strtab_free(res);
			return (NULL);
		}
	}
	return (res);
}

int write_here_doc(char** tab, t_shell *shell)
{
	int i;
	int fd[2];


	if (!tab || !*tab)
		return(-1);
	i = 0;
	expand_vars_heredoc(tab, shell);
	// strtab_print(tab, '\n');
	if (pipe(fd) == -1)
		return(-1);
	while (tab[i])
	{
		// printf("%s\n", tab[i]);
		ft_putstr_fd(tab[i], fd[1]);
		// write(fd[1], tab[i], ft_strlen(tab[i]));
		// write(fd[1], "\n", 1);
		i++;
	}
	// write(fd[1], 0, 0);
	close(fd[1]);
	strtab_free(tab);
	return(fd[0]);
}
