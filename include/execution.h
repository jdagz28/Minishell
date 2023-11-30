/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:09:39 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/30 16:01:26 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

//exec_binpath.c
char	*env_getpath(char *str, char **env);

//exec_utils.c
int		exec_bin(t_simple_cmd *cmd, char **env);

//exec.c
int		exec_node(t_shell *shell, t_node *node);
int		shell_exec(t_shell *shell);

//exec_pipe_utils.c
void	close_pipe(int fd[2]);
void	child_process(int fd[2], t_shell *shell, t_node *node);
void	parent_process(int fd[2], t_shell *shell, t_node *node, int *res);
void	duplicate_restore_fds(int *original_stdin, \
									int *original_stdout, int mode);
void	end_parent(int pid, int *original_stdin, int *original_stdout);

#endif