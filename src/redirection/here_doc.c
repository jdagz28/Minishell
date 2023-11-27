/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 13:26:05 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"

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

int write_here_doc(char** tab)
{
	int i;
	int fd[2];

	if (!tab || !*tab)
		return(-1);
	if (pipe(fd) == -1)
		return(-1);
	i = 0;
	while (tab[i])
	{
		write(fd[1], tab[i], ft_strlen(tab[i]));
		write(fd[1], "\n", 1);
		i++;
	}
	write(fd[1], 0, 1);
	close(fd[1]);
	return(fd[0]);
}
