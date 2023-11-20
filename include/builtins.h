/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:15:05 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/19 23:25:11 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# ifdef LINUX

define PATH_MAX 4096
define NAME_MAX 255

//echo "$(getconf {PATH_MAX / NAME_MAX} /)"
# else
define PATH_MAX 1024
define NAME_MAX 255

# endif

int cd(char **argv, char **env);
int		echo(char **argv);
bool	is_builtin(char **command);
bool	ft_strncmp_twice(const char *s1, const char *s2);

# endif