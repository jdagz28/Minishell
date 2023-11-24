/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:11:54 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/24 00:10:46 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int	update_pwd_error(char *new_pwd)
{
	free(new_pwd);
	return (EXIT_FAILURE);
}

int	cd_error(int error, char *str)
{
	if (error == 0)
	{	
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
	}
	else if (error == 1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("Not a directory\n", STDERR_FILENO);
		free(str);
	}
	else if (error == 2)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	return (EXIT_FAILURE);
}
