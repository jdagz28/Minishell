/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/20 09:23:10 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	write_newline(void)
{
	write(1, "\n", 1);
}

void	prompt_interrupt(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	signal_set(int sig, void *f)
{
	struct sigaction	sa;

	sa.sa_handler = f;
	sa.sa_flags = 0;
	if (sigaction(sig, &sa, NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
