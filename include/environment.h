/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:45 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 10:59:25 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include "minishell.h"
# include "strtab.h"

//env_getvar.c
char* ft_get_env_var(char** environ, const char* var);
char* env_get(char* start, char end, char** env);

//env_set.c
int		ft_setenv(const char* name, const char* value, \
	char*** env, int overwrite);

//var.c
int		vartab_set(char*** tab, char* str);
int		vartab_unset(char*** tab, char* str);
int		vartab_pos(char** tab, char* str);
int		vartab_keypos(char** tab, char* str);
int		key_isvalid(char* str);


#endif
