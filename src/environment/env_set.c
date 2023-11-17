/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 02:08:41 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/17 10:44:04 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

static int	add_var(const char *name, const char *value, char ***new_environ, \
					char *env_var)
{
	char	*var_name_with_eq;
	int		i;
	int		count;

	i = -1;
	count = ft_arraylen(*new_environ);
	var_name_with_eq = ft_strjoin(name, "=");
	if (value)
		env_var = ft_strjoin(var_name_with_eq, value);
	else
		env_var = var_name_with_eq;
	free(var_name_with_eq);
	if (env_var == NULL)
	{
		while (++i < count)
			free(new_environ[i]);
		free(new_environ);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	copy_env(char **new_environ, char ***environ, int env_len)
{
	int	i;

	i = 0;
	while (i < env_len)
	{
		new_environ[i] = ft_strdup(*environ[i]);
		if (new_environ[i] == NULL)
		{
			while (i > 0)
				free(new_environ[i]);
			free(new_environ);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	add_in_env(const char *name, const char *value, char ***env)
{
	char	**environ;
	char	**new_environ;
	int		count;
	char	*env_var;

	env_var = NULL;
	environ = *env;
	count = ft_arraylen(environ); 
	new_environ = (char **)malloc((count + 2) * sizeof(char *));
	if (new_environ == NULL)
		return (EXIT_FAILURE);
	if (copy_env(new_environ, &environ, count) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (add_var(name, value, &new_environ, env_var) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	new_environ[count++] = env_var;
	new_environ[count] = NULL;
	free(environ);
	*env = new_environ;
	return (EXIT_SUCCESS);
}

static int	var_index_env(const char *name, const char **environ)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, len) == 0)
		{
			if (environ[i][len] == '=' || environ[i][len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

int	ft_setenv(const char *name, const char *value, \
				const char **env, int overwrite)
{
	int		i;
	char	**temp;

	temp = (char **)env;
	i = var_index_env(name, env);
	if (i >= 0 && overwrite != 0)
	{
		free(temp[i]);
		if (value == NULL)
			temp[i] = ft_strjoin(name, value);
		else
			temp[i] = ft_strjoin_del(name, value, "=");
		if (temp[i] == NULL)
			return (EXIT_FAILURE);
	}
	else
	{
		if (add_in_env(name, value, &temp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
