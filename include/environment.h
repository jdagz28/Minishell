/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:45 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 09:08:25 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include "minishell.h"

//env_getvar.c
char	*ft_get_env_var(char **environ, const char *var);

//env_set.c
int		ft_setenv(const char *name, const char *value, \
				char ***env, int overwrite);

//strtab_addreplace.c
int		strtab_replace_line(char ***tab, char *str, int id);
int		strtab_add_line(char ***tab, char *str);

//strtab_free.c
void	strtab_free(char **tab);
void	strtab_freeend(char **tab, int start);

//strtab_utils.c
int		strtab_beginwith(char **tab, char *str);
void	strtab_print(char **tab, char ces);
int		strtab_len(char **tab);
char	**strtab_cpy(char **tab);

//var.c
int		var_replace(t_shell *shell, char *str, int id);
int		var_add(t_shell *shell, char *str);
int		var_get_id(char **tab, char *str);
int		var_unset(t_shell *shell, char *str);
int		var_set(t_shell *shell, char *str);

#endif