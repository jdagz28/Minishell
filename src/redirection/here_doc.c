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

int read_here_doc(char* limiter)
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
