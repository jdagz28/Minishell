/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/30 14:59:55 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "lexer_parsing.h"
# include "shell.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>

typedef struct s_pwd	t_pwd;
typedef struct s_user	t_user;

typedef struct s_shell
{
	char	**env;
	char	**var;
	t_pwd	pwd;
	t_user	user;
	t_node	*ast;
	int		err;
	bool	inline_mode;
}	t_shell;

//exit.c
void	shell_clear(t_shell *shell);
void	clean_exit(t_shell *data, int err);

//exit_value.c
int		*get_exit_value(void);
void	set_exit_value(int exit_value);

//signal.c
void	write_newline(void);
void	prompt_interrupt(void);
int		signal_set(int sig, void *f);
void	exit_newline(void);
void	write_quit(void);

// redirection
int		redirect(t_node *node, t_shell *shell);
int		get_here_doc(t_shell *shell, t_simple_cmd *cmd, char *limiter);
int		open_file(char *path, char mode);
int		open_redirections(t_simple_cmd *cmd, t_shell *shell);
void	close_redirect(t_simple_cmd *cmd);

//utils.c
bool	*is_piped(void);
void	set_is_piped(bool value);
void	print_error(char *str1, char *str2);

#endif
