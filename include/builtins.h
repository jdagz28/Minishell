/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:15:05 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/22 11:41:15 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

# ifndef PATH_MAX
#  ifdef LINUX
#   define PATH_MAX 4096
#  else
#   define PATH_MAX 1024
#  endif
# endif

# ifndef NAME_MAX
#  define NAME_MAX 255
# endif

//builtins.c
bool	ft_strncmp_twice(const char* s1, const char* s2);
int		execute_builtin(t_simple_cmd command, t_shell* shell);
bool	is_builtin(char** command);

//cd.c
int		cd(char** argv, char** env);

//cd_errors.c
int		update_pwd_error(char* new_pwd);
int		cd_error(int error, char* str);

//echo.c
int		echo(char** argv);

//export.c
int		export(t_shell* shell, char* str);

//pwd.c
int		pwd(char** argv);

//builtins_utils.c
int	strtab_getkey(char** tab, char* str);

#endif
