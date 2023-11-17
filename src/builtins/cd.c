/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 02:08:41 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/17 09:45:58 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"
#include "builtins.h"

static int	update_pwd(char **argv, char **env)
{
	char	*new_pwd;
	char	*pwd;

	new_pwd = (char *)malloc(PATH_MAX + 1);
	if (!new_pwd)
		return (EXIT_FAILURE);
	if (getcwd(new_pwd, PATH_MAX + 1) == NULL)
	{
		ft_putstr_fd("pwd: getcwd():", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		pwd = ft_strjoin(ft_get_env_var(env, "PWD"), argv[1]);
		if (ft_setenv("PWD", pwd, env, 1) == -1)
		{
			free(new_pwd);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (ft_setenv("PWD", new_pwd, 1) == EXIT_FAILURE)
		{
			free(new_pwd);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

static int	check_stat(char **argv, char *path, struct stat fs)
{
	if (path != NULL && !S_ISDIR(fs.st_mode))
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("Not a directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (path != NULL && chdir(path) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static char	*ft_get_pwd(char *var)
{
	char	*cwd;
	char	*temp;

	cwd = (char *)malloc(PATH_MAX + 1);
	if (!cwd)
		return (NULL);
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
	{
		free(cwd);
		ft_putstr_fd("cd: getcwd():", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	temp = ft_strjoin(var, cwd);
	if (!temp)
		return (NULL);
	free(cwd);
	return (temp);
}

int	cd(char **argv, char **env)
{
	struct stat	fs;
	char		*path;
	char		*pwd;

	if (ft_arraylen(argv) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (ft_arraylen(argv) < 2)
	{
		path = ft_get_env_var(env, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		path = ft_strdup(path);
	}
	else
		path = ft_strdup(argv[1]);
	pwd = ft_get_pwd("OLDPDWD=");
	if (!pwd)
		return (EXIT_FAILURE);
	stat(path, &fs);
	if (check_stat(argv, path, fs) == EXIT_FAILURE)
	{
		free(path);
		return (EXIT_FAILURE);
	}
	free(path);
	if (update_pwd(argv, env) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
