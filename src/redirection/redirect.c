/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/28 14:13:31 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"

void close_redirect(t_simple_cmd* cmd)
{
	if (cmd->fd_input != -1 && cmd->fd_input != 0)
		close(cmd->fd_input);
	if (cmd->fd_output != -1 && cmd->fd_output != 1)
		close(cmd->fd_output);
}

static void redirect_input(t_simple_cmd* cmd, char* type, \
								char* dest, t_shell *shell)
{
	char** here_doc;
	if (cmd->fd_input != -1 && cmd->fd_input != 0)
		close(cmd->fd_input);
	if (ft_strlen(type) == 2 && type[1] == '<')
	{
		here_doc = read_here_doc(dest);
		if (here_doc)
		{
			cmd->fd_input = write_here_doc(here_doc, shell);
			cmd->here_doc = true;
			// strtab_free(here_doc);
		}
	}
	else
		cmd->fd_input = open_file(dest, 'r');
	if (cmd->fd_input == -1)
		print_error(dest, strerror(errno));
}

static void redirect_output(t_simple_cmd* cmd, char* type, char* dest)
{
	char c;

	if (cmd->fd_output != -1 && cmd->fd_output != 1)
		close(cmd->fd_output);
	c = 'w';
	if (ft_strlen(type) == 2 && type[1] == '>')
		c = 'a';
	cmd->fd_output = open_file(dest, c);
	if (cmd->fd_output == -1)
		print_error(dest, strerror(errno));
}

int redirect_one(t_simple_cmd* cmd, char* type, char* dest, t_shell *shell)
{
	char c;

	//ft_printf("%s %s\n", type, dest);
	c = type[0];
	if (c == '<')
		redirect_input(cmd, type, dest, shell);
	else if (c == '>')
		redirect_output(cmd, type, dest);
	else
		return(0);
	return(1);
}

int redirect(t_simple_cmd* cmd, t_shell *shell)
{
	int i;
	char** argv;

	argv = cmd->argv;
	i = 0;
	while (i < strtab_len(argv))
	{
		if (redirect_one(cmd, argv[i], argv[i + 1], shell))
		{
			strtab_remove_mult(&cmd->argv, i, 2);
			argv = cmd->argv;
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
