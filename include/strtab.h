/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtab.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:34:45 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/30 15:02:13 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRTAB_H
# define STRTAB_H
# include "minishell.h"

//strtab_addreplace.c
int		strtab_replace(char **tab, char *str, int id);
int		strtab_add(char ***tab, char *str);
int		strtab_remove(char ***tab, int id);
int		strtab_remove_mult(char ***tab, int id, int len);

//strtab_free.c
void	strtab_free(char **tab);
void	strtab_freeend(char **tab, int start);

//strtab_utils.c
int		strtab_beginwith(char **tab, char *str);
void	strtab_print(char **tab, char ces);
void	strtab_write(char **tab, char ces, int fd);
int		strtab_len(char **tab);
char	**strtab_cpy(char **tab);
#endif
