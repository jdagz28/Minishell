/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/31 01:18:55 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
#include "../libft/libft.h"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

typedef struct s_var
{
    char *key;
    char *value;
} t_var;

typedef struct s_pwd
{
    char *root;
    char *home;
} t_pwd;

typedef struct s_user
{
    char *username;
    char *machinename;
    char *lastinput;
} t_user;

typedef struct s_cmd
{
    char ***cmd;
    int len;
    int (*pipes)[2];
} t_cmd;

typedef struct s_shell
{
    char **env;
    t_list **var;
    int err;
    t_pwd pwd;
    t_user user;
    t_cmd cmd;
} t_shell;

/* strtab_utils */
int strtab_len(char **tab);
char **strtab_cpy(char **tab);
void strtab_free(char **tab);
char *strtab_beginwith(char **tab, char *str);
void strtab_print(char **cmd, char ces);
/* strmatrix_utils */
int strmatrix_len(char ***matrix);
char ***strtab_split(char **tab, char c);
void strmatrix_free(char ***matrix);
void strmatrix_print(char ***matrix, char cesa, char cesb);
/* shell */
int shell_init(t_shell *shell, char *cmds, char **env);
void shell_clear(t_shell *shell);
int shell_prompt(t_shell *shell);
int shell_exec_all(t_shell *shell);
int shell_exec(char **tab, t_cmd *cmd, int id, char **env);
/* env */
char *env_get(char *start, char end, char **env);
char *env_getpath(char *str, char **env);
/* user */
int user_init(t_user *user, char **env);
void user_clear(t_user *user);
int user_setlastinput(t_user *user, char *str);
char *user_cat(t_user *user);
/* pwd */
int pwd_init(t_pwd *pwd, char **env);
void pwd_clear(t_pwd *pwd);
char *pwd_cat(t_pwd *pwd);
/* command */
int command_init(t_cmd *cmd, char *str);
int command_clear(t_cmd *cmd);
void command_exec(char **cmd, char **env);
/* pipes file descriptors*/
int (*pipes_init(int len))[2];
void pipes_close(int (*pipes)[2], int len);
void pipes_dup(int (*pipes)[2], int id, int len);
/* utils */
void print_error(char *str1, char *str2);
void clean_exit(t_shell *data, int err);

#endif
