/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 02:30:33 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/23 15:09:29 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal.h"
#include "shell.h"
#include "execution.h"


static char* shell_readline(t_shell* shell)
{
	char* cat;
	char* line;

	cat = shell_cat(shell);
	if (!cat)
		return (NULL);
	signal_set(SIGINT, &prompt_interrupt);
	line = readline(cat);
	signal_set(SIGINT, &write_newline);
	free(cat);
	if (!line)
	{
		write(1, "exit\n", 5);
		exit(128);
	}
	user_setlastinput(&shell->user, line);
	return (line);
}

void	shell_prompt(t_shell* shell)
{
	char* line;
	int		err;

	line = shell_readline(shell);
	shell->ast = parse(line);
	if (line)
		free(line);
	//if (!shell->ast)
	//	set_exit_value(EXIT_FAILURE);
	err = shell_exec(shell);
	clear_ast(&shell->ast);
	set_exit_value(err);
}
