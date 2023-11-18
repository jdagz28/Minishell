/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/13 21:08:55 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void clean_exit(t_shell *data, int err)
{
    rl_clear_history();
    shell_clear(data);
    exit(err);
}

void print_error(char *str1, char *str2)
{
    write(STDERR_FILENO, "minishell: ", 11);
    write(STDERR_FILENO, str1, ft_strlen(str1));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, str2, ft_strlen(str2));
    write(STDERR_FILENO, "\n", 1);
}
