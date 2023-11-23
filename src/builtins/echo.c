/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:59:25 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/23 09:26:26 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "expansion.h"

int	echo(char **argv)
{
	int		i;
	bool	dash_flag;

	i = 1;
	dash_flag = false;
	if (ft_arraylen(argv) >= 2 && ft_strncmp_twice(argv[i], "-n") == true)
	{
		i = 2;
		dash_flag = true;
	}
	if (dash_flag == false && ft_arraylen(argv) >= 2 && \
			ft_strncmp_twice(argv[i], "-n") == false)
		i = 2;
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (argv == NULL || dash_flag == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
