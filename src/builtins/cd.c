/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 02:08:41 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/30 15:19:25 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"
#include "expansion.h"
#include "builtins.h"
#include "environment.h"
#include "strtab.h"

static int	update_pwd(char **argv, char **env)
{
	char	*new_pwd;
	char	*pwd;

	new_pwd = (char *)malloc(PATH_MAX + 1);
	if (new_pwd == NULL)
		return (EXIT_FAILURE);
	if (getcwd(new_pwd, PATH_MAX + 1) == NULL)
	{
		ft_putstr_fd("pwd: getcwd():", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		pwd = ft_strjoin(ft_get_env_var(env, "PWD"), argv[1]);
		if (pwd == NULL)
			return (EXIT_FAILURE);
		if (ft_setenv("PWD", pwd, &env, 1) == -1)
			return (update_pwd_error(new_pwd));
	}
	else
	{
		if (ft_setenv("PWD", new_pwd, &env, 1) == EXIT_FAILURE)
			return (update_pwd_error(new_pwd));
	}
	free(new_pwd);
	return (EXIT_SUCCESS);
}

static char	*ft_get_pwd(char *var)
{
	char	*cwd;
	char	*temp;

	cwd = (char *)malloc(PATH_MAX + 1);
	if (cwd == NULL)
		return (NULL);
	if (getcwd(cwd, PATH_MAX + 1) == NULL)
	{
		free(cwd);
		ft_putstr_fd("cd: getcwd():", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	temp = ft_strjoin(var, cwd);
	if (temp == NULL)
		return (NULL);
	free(cwd);
	return (temp);
}

static char	*get_home_path(char **env)
{
	char	*home_path;

	home_path = ft_get_env_var(env, "HOME");
	if (home_path == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (ft_strdup(home_path));
}

int	cd(char **argv, char **env)
{
	struct stat	fs;
	char		*path;
	char		*pwd;

	if (strtab_len(argv) > 2)
		return (cd_error(0, NULL));
	if (strtab_len(argv) < 2)
		path = get_home_path(env);
	else
		path = ft_strdup(argv[1]);
	pwd = ft_get_pwd("OLDPDWD=");
	if (path == NULL || pwd == NULL)
		return (EXIT_FAILURE);
	stat(path, &fs);
	if (!S_ISDIR(fs.st_mode))
		return (cd_error(1, path));
	if (chdir(path) == -1)
		return (cd_error(2, argv[0]));
	free(path);
	if (update_pwd(argv, env) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
