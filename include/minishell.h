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
#include "./lexer_parsing.h"
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>

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

typedef struct s_shell
{
    char **env;
    char **var;
    t_pwd pwd;
    t_user user;
    t_node *ast;
    int err;
} t_shell;

/* strtab_utils */
int strtab_len(char **tab);
char **strtab_cpy(char **tab);
void strtab_free(char **tab);
void strtab_freeend(char **tab, int start);
int strtab_beginwith(char **tab, char *str);
void strtab_print(char **cmd, char ces);
int strtab_replace_line(char ***tab, char *str, int id);
int strtab_add_line(char ***tab, char *str);
/* strmatrix_utils */
int strmatrix_len(char ***matrix);
char ***strtab_split(char **tab, char c);
void strmatrix_free(char ***matrix);
void strmatrix_print(char ***matrix, char cesa, char cesb);
/* shell */
int shell_init(t_shell *shell, char *cmds, char **env);
void shell_clear(t_shell *shell);
int shell_run(t_shell *shell);
int shell_prompt(t_shell *shell);
int shell_exec(t_shell *shell);
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
/* files redirections */
int open_file_dup2(char *path, char mode);
char **files_redirect(char **tab);
/* utils */
void print_error(char *str1, char *str2);
void clean_exit(t_shell *data, int err);
/* exec */
int exec_node(t_shell *shell, t_node *node);
int exec_simple(t_shell *shell, t_node *node);
int exec_pipe(t_shell *shell, t_node *node);
int exec_bin(t_simple_cmd *cmd, char **env);
int exec_builtin(t_shell *shell, char **cmd);
/* signals */
void prompt_interrupt();
int signal_set(int sig, void *f);
void write_newline();
/* export */
int export(t_shell *shell, char *str);
/* var */
int var_set(t_shell *shell, char *str);
int var_get_id(char **tab, char *str);

#endif
