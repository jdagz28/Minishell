/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/20 11:01:25 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"
#include "signal.h"
#include "builtins.h"
#include "shell.h"

int	shell_init(t_shell* shell, char* cmds, char** env)
{
	shell->env = strtab_cpy(env);
	shell->err = 0;
	shell->var = NULL;
	if (!shell->env)
		return (EXIT_FAILURE);
	shell->ast = parse(cmds);
	if (cmds && !shell->ast)
		return (EXIT_FAILURE);
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

int	shell_run(t_shell* shell)
{
	signal_set(SIGQUIT, SIG_IGN);
	vartab_set(&shell->var, "toto=caca");
	/*export(shell, "3caca=3");
	unset(shell, "cac");*/
	while (shell->err != 128)
		shell->err = shell_prompt(shell);
	ft_printf("exit\n");
	return (128);
}

