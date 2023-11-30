/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/30 09:55:25 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"
#include "lexer_parsing.h"
#include "builtins.h"

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
		if (cmd->fd_input != STDIN_FILENO)
			close(cmd->fd_input);
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

static void	remove_redirect_argv(char **argv)
{
	int	i;

	i = 2;
	while (argv[i] != NULL)
	{
		argv[i - 2] = argv[i];
		i++;
	}
	argv[i - 2] = argv[i];
}

static int	open_redirections(t_simple_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < strtab_len(cmd->argv))
	{
		if (is_redirect(cmd->argv[i]) == true)
		{
			if ((int)ft_strlen(cmd->argv[i + 1]) > 255)
			{
				print_error(cmd->argv[i + 1], "file name too long");
				return (false);
			}
			if (redirect_one(cmd, cmd->argv[i], cmd->argv[i + 1], shell) == false)
				return (false);
			remove_redirect_argv(&cmd->argv[i]);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}

int redirect(t_node *node, t_shell *shell)
{
	if (node->type == SIMPLE_CMD)
	{
		return (open_redirections(&node->content.simple_cmd, shell));
	}
	else
	{
		if (node->content.child.left != NULL)
			if (redirect(node->content.child.left, shell) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		if (node->content.child.right != NULL)
			if (redirect(node->content.child.right, shell) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
}
