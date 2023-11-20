/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:39 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 09:12:41 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

//exec_binpath.c
char	*env_get(char *start, char end, char **env);
char	*env_getpath(char *str, char **env);

//exec_utils.c
int		exec_bin(t_simple_cmd *cmd, char **env);

//exec.c
int		shell_exec(t_shell *shell);

#endif