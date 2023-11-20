/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 02:08:41 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 10:51:21 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"
#include "environment.h"

static char	**append_new_environ(char **new_environ, char *env_var)
{
	int		count;
	int		i;
	char	**new_array;

	count = ft_arraylen(new_environ);
	new_array = (char **)malloc((count + 2) * sizeof(char *));
	if (new_array == NULL)
	{
		free(env_var);
		return (NULL);
	}
	i = -1;
	while (++i < count)
		new_array[i] = new_environ[i];
	new_array[count++] = env_var;
	new_array[count] = NULL;
	free(new_environ);
	return (new_array);
}

static char	**copy_env(char **environ)
{
	int		i;
	int		count;
	char	**new_environ;

	count = ft_arraylen(environ);
	new_environ = strtab_cpy(environ);
	if (new_environ == NULL)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		if (new_environ[i] == NULL)
		{
			while (i--)
				free(new_environ[i]);
			free(new_environ);
			return (NULL);
		}
	}
	return (new_environ);
}

static int	add_in_env(const char *name, const char *value, char ***env)
{
	char	**environ;
	char	**new_environ;
	char	*env_var;
	char	*name_with_eq;

	env_var = NULL;
	environ = *env;
	new_environ = copy_env(environ);
	if (new_environ == NULL)
		return (EXIT_FAILURE);
	name_with_eq = ft_strjoin(name, "=");
	if (value)
		env_var = ft_strjoin(name_with_eq, value);
	else
		env_var = name_with_eq;
	free(name_with_eq);
	if (env_var == NULL)
	{
		strtab_free(new_environ);
		return (EXIT_FAILURE);
	}
	*env = append_new_environ(new_environ, env_var);
	strtab_free(environ);
	return (EXIT_SUCCESS);
}

static int	var_index_env(const char *name, char **environ)
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
				char ***env, int overwrite)
{
	int		i;
	char	**temp;
	char	*new_value;

	temp = *env;
	i = var_index_env(name, *env);
	if (i >= 0 && overwrite != 0)
	{
		if (value == NULL)
			new_value = ft_strjoin(name, "=");
		else
			new_value = ft_strjoin_del(name, value, "=");
		if (new_value == NULL)
			return (EXIT_FAILURE);
		free(temp[i]);
		temp[i] = new_value;
	}
	else
	{
		if (add_in_env(name, value, env) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
