/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/27 20:33:56 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"

int read_here_doc(t_simple_cmd* cmd, char* limiter)
{
	char* line;
	int len;
	int err;

	len = ft_strlen(limiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_error("warning: here-document at line 1 delimited by end-of-file, wanted: ", limiter);
			return(EXIT_SUCCESS);
		}
		if (ft_strncmp(line, limiter, len) == 0)
		{
			free(line);
			break;
		}
		err = strtab_add(&cmd->here_doc, line);
		if (err)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


int write_here_doc(t_simple_cmd* cmd)
{
	int i;
	char** tab;

	tab = cmd->here_doc;
	if (!tab || !*tab)
		return(EXIT_FAILURE);
	i = 0;
	while (tab[i])
	{
		write(STDIN_FILENO, tab[i], ft_strlen(tab[i]));
		write(STDIN_FILENO, "\n", 1);
		i++;
	}
	write(STDIN_FILENO, 0, 0);
	return(EXIT_SUCCESS);
}
