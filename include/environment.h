/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:45 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/17 10:48:35 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

//env_getvar.c
char	*ft_get_env_var(char **environ, const char *var);

//env_set.c
int		ft_setenv(const char *name, const char *value, \
				const char **env, int overwrite);
#endif