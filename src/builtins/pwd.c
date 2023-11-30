/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 03:02:35 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/30 14:46:22 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "environment.h"

int	pwd(char **argv, int fd)
{
	char	pwd[PATH_MAX];
	int		count;

	count = strtab_len(argv);
	if (count > 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		ft_putstr_fd("pwd: getcwd(): ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	return (EXIT_SUCCESS);
}
