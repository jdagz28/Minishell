/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 00:23:51 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/24 15:35:36 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "environment.h"

bool	ft_strncmp_twice(const char* s1, const char* s2) // == ft_strncmp(str1, str2, ft_strlen(str1 + 1));
{
	if (ft_strncmp(s1, s2, ft_strlen(s1)) == 0 \
		&& ft_strncmp(s1, s2, ft_strlen(s2)) == 0)
		return (true);
	return (false);
}

int	execute_builtin(t_simple_cmd command, t_shell* shell)
{
	int	status;

	status = -1;
	if (ft_strncmp_twice((const char*)command.argv[0], "env"))
	{
		strtab_print(shell->env, '\n');
		status = EXIT_SUCCESS;
	}
	if (ft_strncmp_twice((const char*)command.argv[0], "cd"))
	{
		status = cd(command.argv, shell->env);
		shell->pwd.root = env_get("PWD=", 0, shell->env);
		if (shell->pwd.root == NULL)
			return (EXIT_FAILURE);
	}
	if (ft_strncmp_twice((const char*)command.argv[0], "echo"))
		status = echo(command.argv);
	if (ft_strncmp_twice((const char*)command.argv[0], "pwd"))
		status = pwd(command.argv);
	if (ft_strncmp_twice((const char*)command.argv[0], "export"))
		status = export(shell, command.argv[1]);
	if (ft_strncmp_twice((const char*)command.argv[0], "unset"))
		status = unset(shell, command.argv[1]);
	status = var_set(shell, command.argv);
	if (ft_strncmp_twice((const char*)command.argv[0], "exit"))
		status = builtin_exit(command.argv, shell);
	if (status != EXIT_SUCCESS)
		return(EXIT_FAILURE); 
	return (status);
}

bool	is_builtin(char** command)
{
	if (command == NULL || command[0] == NULL)
		return (false);
	if (ft_strncmp_twice((const char*)command[0], "echo"))
		return (true);
	if (ft_strncmp_twice((const char*)command[0], "cd"))
		return (true);
	if (ft_strncmp_twice((const char*)command[0], "pwd"))
		return (true);
	if (ft_strncmp_twice((const char*)command[0], "export"))
		return (true);
	if (ft_strncmp_twice((const char*)command[0], "unset"))
		return (true);
	if (ft_strncmp_twice((const char*)command[0], "env"))
		return (true);
	if (ft_strncmp_twice((const char*)command[0], "exit"))
		return (true);
	if (ft_strchr(command[0], '='))
		return (true);
	return (false);
}
