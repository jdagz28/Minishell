/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:04:33 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/22 14:06:33 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_exit_value(void)
{
	static int	exit_value = 0;

	return (&exit_value);
}

void	set_exit_value(int exit_value)
{
	*get_exit_value() = exit_value;
}
