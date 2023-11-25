/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/25 15:44:26 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "shell.h"

int	main(int argc, char** argv, char** env)
{
	t_shell	shell;
	char* cmds;
	int		err;

	(void)argc;
	(void)argv;
	cmds = NULL;
	if (shell_init(&shell, cmds, env))
		return (*get_exit_value());
	if (cmds)
		err = shell_exec(&shell);
	else
		shell_run(&shell);
	shell_clear(&shell);
	return (err);
}
