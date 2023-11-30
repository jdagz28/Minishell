/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:18:51 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/30 15:01:29 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

typedef struct s_pwd
{
	char	*root;
	char	*home;
}	t_pwd;

typedef struct s_user
{
	char	*username;
	char	*machinename;
	char	*lastinput;
}	t_user;

typedef struct s_shell	t_shell;

//init_pwd.c
int		pwd_init(t_pwd *pwd, char **env);
void	pwd_clear(t_pwd *pwd);
char	*pwd_cat(t_pwd *pwd);

//shell_prompt.c
void	shell_prompt(t_shell *shell);

//shell.c
int		shell_init(t_shell *shell, char **env);
int		shell_init_level(t_shell *shell);
char	*shell_cat(t_shell *shell);
void	shell_run(t_shell *shell);

//user.c
int		user_init(t_user *user, char **env);
void	user_clear(t_user *user);
int		user_setlastinput(t_user *user, char *str);
char	*user_cat(t_user *user);

#endif
