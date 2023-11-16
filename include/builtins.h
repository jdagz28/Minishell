/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:15:05 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/16 15:22:13 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# ifdef LINUX

define PATH_MAX 4096
define NAME_MAX 255

//!check PATH_MAX and NAME_MAX at 19
// # else
// define PATH_MAX 
// define NAME_MAX

# endif

#endif