/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/27 20:57:43 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"
#include "signal.h"
#include "builtins.h"
#include "shell.h"

static bool	check_inline_mode(void)
{
	return (isatty(STDIN_FILENO) == 0);
}

int	shell_init(t_shell* shell, char** env)
{
	shell->env = strtab_cpy(env);
	shell->err = 0;
	shell->var = NULL;
	if (!shell->env)
		return (EXIT_FAILURE);
	shell->inline_mode = check_inline_mode();
	shell->ast = NULL;
	shell_init_level(shell);
	if (user_init(&shell->user, env) || pwd_init(&shell->pwd, env))
	{
		shell_clear(shell);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char* shell_cat(t_shell* shell)
{
	char* res;
	char* user;
	char* pwd;

	user = user_cat(&shell->user);
	pwd = pwd_cat(&shell->pwd);
	res = ft_strjoin(user, pwd);
	free(user);
	free(pwd);
	return (res);
}

void	shell_run(t_shell* shell)
{
	signal_set(SIGQUIT, SIG_IGN);
	while (shell->err != 128)
		shell_prompt(shell);
}

