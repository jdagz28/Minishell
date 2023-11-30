/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/30 13:47:56 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	write_newline(void)
{
	write(1, "\n", 1);
	set_exit_value(1);
}

void	exit_newline(void)
{
	write_newline();
	exit(*get_exit_value());
}

void	write_quit(void)
{
	write(1, "Quit: 3\n", 8);
	set_exit_value(131);
}

void	prompt_interrupt(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_value(1);
}

int	signal_set(int sig, void *f)
{
	struct sigaction	sa;

	sa.sa_handler = f;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(sig, &sa, NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
