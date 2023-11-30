/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/30 14:35:48 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "strtab.h"
#include "builtins.h"

int	shell_init_level(t_shell *shell)
{
	char	*line;
	char	*res;
	char	*level;
	int		value;
	int		len;

	line = env_get("SHLVL=", 0, shell->env);
	if (!line)
		return (EXIT_FAILURE);
	value = ft_atoi(line);
	level = ft_itoa(value + 1);
	free(line);
	len = ft_strlen("SHLVL=") + ft_strlen(level) + 1;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (EXIT_FAILURE);
	ft_strlcpy(res, "SHLVL=", len);
	ft_strlcat(res, level, len);
	export(shell, res);
	free(level);
	free(res);
	return (EXIT_SUCCESS);
}
