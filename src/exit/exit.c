/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 02:28:33 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 12:01:50 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

void	shell_clear(t_shell *shell)
{
	if (shell->env)
		strtab_free(shell->env);
	if (shell->ast)
		clear_ast(&shell->ast);
	user_clear(&shell->user);
	pwd_clear(&shell->pwd);
}

void	clean_exit(t_shell *data, int err)
{
	rl_clear_history();
	shell_clear(data);
	exit(err);
}
