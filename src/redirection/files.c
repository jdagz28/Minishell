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

static int read_here_doc(char* limiter)
{
	char* line;
	char* red;
	int len;

	red = NULL;
	len = ft_strlen(limiter);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, len) == 0)
		{
			free(line);
			break;
		}
		red = ft_stradd(red, line);
		free(line);
		if (red == NULL)
			return (EXIT_FAILURE);
	}
	write(STDIN_FILENO, red, ft_strlen(red) + 1);
	free(red);
	return (EXIT_SUCCESS);
}

static int check_access(char* path, char mode)
{
	if (ft_strlen(path) == 0)
	{
		print_error("", "No such file or directory");
		return (EXIT_FAILURE);
	}
	if (mode == 'r')
		return (EXIT_SUCCESS);
	if (access(path, F_OK) == 0 && access(path, W_OK) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int open_file_dup2(char* path, char mode)
{
	int err;
	int fd;

	if (check_access(path, mode))
		return (EXIT_FAILURE);
	if (mode == 'r')
		fd = open(path, O_RDONLY);
	else if (mode == 'w')
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (mode == 'a')
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (mode == 'r')
		err = dup2(fd, STDIN_FILENO);
	else
		err = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (err == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char** files_redirect(char** tab)
{
	int len;
	char c;

	len = strtab_len(tab);
	if (len > 1 && tab[0][0] == '<')
	{
		if (strlen(tab[0]) > 1 && tab[0][1] == '<')
			read_here_doc(tab[1]);
		else if (open_file_dup2(tab[1], 'r'))
			print_error(tab[1], strerror(errno));
		if (len > 2)
			tab = &tab[2];
		else
			tab = NULL;
	}
	len = strtab_len(tab);
	if (strtab_len(tab) > 2 && tab[len - 2][0] == '>')
	{
		c = 'w';
		if (strlen(tab[len - 2]) > 1 && tab[len - 2][1] == '>')
			c = 'a';
		if (open_file_dup2(tab[len - 1], c))
			print_error(tab[len - 1], strerror(errno));
		strtab_freeend(tab, len - 2);
	}
	return (tab);
}
