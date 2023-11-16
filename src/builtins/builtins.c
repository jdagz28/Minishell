/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 00:23:51 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/16 09:54:04 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp_twice(const char *s1, const char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0 \
			&& ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_simple_cmd command)
{
	int	status;

	status = -1;
	if (ft_strncmp_twice((const char *)command.argv[0], "exit"))
	{	
		//TODO: close(IO_file)
        //TODO: exit
	}
	if (ft_strncmp_twice((const char *)command.argv[0], "echo"))
		status = echo(command.argv);
	if (ft_strncmp_twice((const char *)command.argv[0], "env"))
        //TODO: link env(from toto)
	if (ft_strncmp_twice((const char *)command.argv[0], "cd"))
		status = cd(command.argv);
	if (ft_strncmp_twice((const char *)command.argv[0], "pwd"))
		//TODO: link pwd(from toto)
        status = pwd();
	if (status != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
}

bool	is_builtin(char **command)
{
	if (command == NULL || command[0] == NULL)
		return (false);
	if (ft_strncmp_twice((const char *)command[0], "echo"))
		return (true);
	if (ft_strncmp_twice((const char *)command[0], "cd"))
		return (true);
	if (ft_strncmp_twice((const char *)command[0], "pwd"))
		return (true);
	if (ft_strncmp_twice((const char *)command[0], "export"))
		return (true);
	if (ft_strncmp_twice((const char *)command[0], "unset"))
		return (true);
	if (ft_strncmp_twice((const char *)command[0], "env"))
		return (true);
	if (ft_strncmp_twice((const char *)command[0], "exit"))
		return (true);
	return (false);
}
