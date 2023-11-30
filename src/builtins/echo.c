/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 23:59:25 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/30 15:27:44 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "expansion.h"
#include "strtab.h"

static bool	check_option(int arg_i, char *argv, bool *dash_flag)
{
	size_t	i;

	i = 2;
	while (i < ft_strlen(argv) && argv[i] == 'n')
		i++;
	if (i == ft_strlen(argv))
	{
		if (arg_i == 1)
			*dash_flag = true;
		return (true);
	}
	else
		return (false);
}

int	echo(char **argv, int fd)
{
	int		i;
	bool	dash_flag;

	i = 1;
	dash_flag = false;
	if (strtab_len(argv) >= 2)
	{
		while (ft_strncmp(argv[i], "-n", ft_strlen("-n")) == 0)
		{
			if (check_option(i, argv[i], &dash_flag) == false)
				break ;
			i++;
		}
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
