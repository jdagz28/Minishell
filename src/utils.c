/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/23 08:58:08 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	*is_piped(void)
{
	static bool	is_piped = false;

	return (&is_piped);
}

void	set_is_piped(bool value)
{
	*is_piped() = value;
}

void	print_error(char *str1, char *str2)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, str1, ft_strlen(str1));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str2, ft_strlen(str2));
	write(STDERR_FILENO, "\n", 1);
}
