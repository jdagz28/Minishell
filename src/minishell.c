/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/27 20:56:29 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "shell.h"

int	main(int argc, char** argv, char** env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	if (shell_init(&shell, env))
		return (EXIT_FAILURE);
	shell_run(&shell);
	shell_exec(&shell);
	shell_clear(&shell);
	return (shell.err);
}
