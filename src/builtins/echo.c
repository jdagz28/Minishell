/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:59:25 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/27 10:10:39 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "expansion.h"

static bool	check_option(char *argv, bool *dash_flag)
{
	size_t	i;

	i = 2;

	while (i < ft_strlen(argv) && argv[i] == 'n')
		i++;
	if (i == ft_strlen(argv))
	{
		*dash_flag = true;
		return (true);
	}
	else
		return (false); 
}

int	echo(char **argv)
{
	int		i;
	bool	dash_flag;

	i = 0;
	dash_flag = false;
	if (ft_arraylen(argv) >= 2)
	{
		while (ft_strncmp(argv[++i], "-n", ft_strlen("-n")) == 0)
			if (check_option(argv[i], &dash_flag) == false)
				break ;
	}
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], fd);
		i++;
		if (argv[i] != NULL)
			ft_putchar_fd(' ', fd);
	}
	if (argv == NULL || dash_flag == false)
		ft_putstr_fd("\n", fd);
	return (EXIT_SUCCESS);
}
