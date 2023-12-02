/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/12/02 20:45:27 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"
#include "lexer_parsing.h"
#include "builtins.h"

static void	redirect_input(t_simple_cmd *cmd, char *type, \
								char *dest, t_shell *shell)
{
	int	err;

	if (cmd->fd_input != -1 && cmd->fd_input != 0)
		close(cmd->fd_input);
	if (ft_strlen(type) == 2 && type[1] == '<')
	{
		if (cmd->fd_input != STDIN_FILENO)
			close(cmd->fd_input);
		err = get_here_doc(shell, cmd, dest);
		set_exit_value(err);
		cmd->here_doc = true;
	}
	else
		cmd->fd_input = open_file(dest, 'r');
	if (cmd->fd_input == -1 && cmd->here_doc == 0)
		print_error(dest, strerror(errno));
}

static void	redirect_output(t_simple_cmd *cmd, char *type, char *dest)
{
	char	c;

	if (cmd->fd_output != -1 && cmd->fd_output != 1)
		close(cmd->fd_output);
	c = 'w';
	if (ft_strlen(type) == 2 && type[1] == '>')
		c = 'a';
	cmd->fd_output = open_file(dest, c);
	if (cmd->fd_output == -1)
		print_error(dest, strerror(errno));
}

int	redirect_one(t_simple_cmd *cmd, char *type, char *dest, t_shell *shell)
{
	char	c;

	c = type[0];
	if (c == '<')
		redirect_input(cmd, type, dest, shell);
	else if (c == '>')
		redirect_output(cmd, type, dest);
	else
		return (0);
	return (1);
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

int	open_redirections(t_simple_cmd *cmd, t_shell *shell)
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
				return (EXIT_FAILURE);
			}
			if (redirect_one(cmd, \
					cmd->argv[i], cmd->argv[i + 1], shell) == false)
				return (EXIT_FAILURE);
			remove_redirect_argv(&cmd->argv[i]);
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
