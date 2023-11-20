/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:18:51 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 09:22:28 by jdagoy           ###   ########.fr       */
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

//init_pwd.c
int		pwd_init(t_pwd *pwd, char **env);
void	pwd_clear(t_pwd *pwd);
char	*pwd_cat(t_pwd *pwd);

//shell_prompt.c
int		shell_prompt(t_shell *shell);

//shell.c
int		shell_init(t_shell *shell, char *cmds, char **env);

//user.c
int		user_init(t_user *user, char **env);
void	user_clear(t_user *user);


#endif