/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:59:25 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/25 19:57:44 by jdagoy           ###   ########.fr       */
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
		i++;
		dash_flag = true;
	}
	if (ft_arraylen(argv) >= 2 && ft_strncmp(argv[i], "-n", \
		ft_strlen("-n")) == 0 && ft_strncmp_twice(argv[i], "-n") == false)
		i++;
	while (dash_flag == true && ft_strncmp_twice(argv[i], "-n") == true)
		i++;
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
