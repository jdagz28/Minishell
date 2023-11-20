/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/20 02:31:00 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	shell_init(t_shell *shell, char *cmds, char **env)
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

static char	*shell_cat(t_shell *shell)
{
	char	*res;
	char	*user;
	char	*pwd;

	user = user_cat(&shell->user);
	pwd = pwd_cat(&shell->pwd);
	res = ft_strjoin(user, pwd);
	free(user);
	free(pwd);
	return (res);
}

int	shell_run(t_shell *shell)
{
	signal_set(SIGQUIT, SIG_IGN);
	var_set(shell, "toto=1");
	export(shell, "tot");
	while (shell->err != 128)
		shell->err = shell_prompt(shell);
	ft_printf("exit\n");
	return (128);
}

