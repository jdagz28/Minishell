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

int open_file(char* path, char mode)
{
	int fd;

	fd = -1;
	if (check_access(path, mode))
		return (fd);
	if (mode == 'r')
		fd = open(path, O_RDONLY);
	else if (mode == 'w')
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (mode == 'a')
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0664);
	return(fd);
}
