/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/20 11:11:43 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "execution.h"
#include "shell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*cmds;
	int		err;

	if (argc == 1)
		cmds = NULL;
	else
		cmds = argv[1];
	if (shell_init(&shell, cmds, env))
		return (EXIT_FAILURE);
	if (cmds)
		err = shell_exec(&shell);
	else
		shell_run(&shell);
	shell_clear(&shell);
	return (err);
}
