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

static void redirect_input(t_simple_cmd* cmd, char* type, char* dest)
{
	if (ft_strlen(type) == 2 && type[1] == '<')
		cmd->here_doc = true;
	else
		cmd->fd_input = open_file(dest, 'r');
	if (cmd->fd_input == -1)
		print_error(dest, strerror(errno));
}

static void redirect_output(t_simple_cmd* cmd, char* type, char* dest)
{
	char c;

	c = 'w';
	if (ft_strlen(type) == 2 && type[1] == '>')
		c = 'a';
	cmd->fd_output = open_file(dest, c);
	if (cmd->fd_output == -1)
		print_error(dest, strerror(errno));
}

int redirect_one(t_simple_cmd* cmd, char* type, char* dest)
{
	char c;

	//ft_printf("%s %s\n", type, dest);
	c = type[0];
	if (c == '<')
		redirect_input(cmd, type, dest);
	else if (c == '>')
		redirect_output(cmd, type, dest);
	else
		return(0);
	return(1);
}

int redirect(t_simple_cmd* cmd)
{
	int i;
	char** argv;

	argv = cmd->argv;
	i = 0;
	while (i < strtab_len(argv))
	{
		if (redirect_one(cmd, argv[i], argv[i + 1]))
		{
			strtab_remove_mult(&cmd->argv, i, 2);
			argv = cmd->argv;
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
