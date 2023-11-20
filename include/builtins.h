/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:15:05 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 09:12:52 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

# ifdef LINUX

define PATH_MAX 4096
define NAME_MAX 255

//echo "$(getconf {PATH_MAX / NAME_MAX} /)"
# else
define PATH_MAX 1024
define NAME_MAX 255

# endif

//builtins.c
bool	ft_strncmp_twice(const char *s1, const char *s2);
void	execute_builtin(t_simple_cmd command, t_shell *shell);
bool	is_builtin(char **command);

//cd.c
int		cd(char **argv, char **env);

//echo.c
int		echo(char **argv);

//export.c
int		export(t_shell *shell, char *str);

//pwd.c
int		pwd(char **argv);

# endif