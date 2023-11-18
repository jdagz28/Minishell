/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 13:26:05 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void write_newline()
{
    write(1, "\n", 1);
}

void prompt_interrupt()
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

int signal_set(int sig, void *f)
{
    struct sigaction sa;

    sa.sa_handler = f;
    sa.sa_flags = 0;

    if (sigaction(sig, &sa, NULL) != 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
