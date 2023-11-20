/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 03:02:35 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 03:12:04 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"
#include "builtins.h"

int	pwd_error(void)
{
	ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	pwd(char **argv)
{
	char	pwd[PATH_MAX];
	int		count;

	count = strtab_len(argv);
	if (count > 1)
		return (pwd_error());
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		ft_putstr_fd("pwd: getcwd(): ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
