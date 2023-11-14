/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 03:16:12 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/14 13:42:48 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char ***array)
{
	int	i;

	i = 0;
	while ((*array)[i] != NULL)
	{
		free((*array)[i]);
		++i;
	}
}

void print_error(char *str1, char *str2)
{
    write(STDERR_FILENO, "minishell: ", 11);
    write(STDERR_FILENO, str1, ft_strlen(str1));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, str2, ft_strlen(str2));
    write(STDERR_FILENO, "\n", 1);
}
