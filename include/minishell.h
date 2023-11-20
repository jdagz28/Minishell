/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/20 11:18:22 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "lexer_parsing.h"
# include "shell.h"
# include <stdio.h>
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
}	t_shell;

//exit.c
void	shell_clear(t_shell *shell);
void	clean_exit(t_shell *data, int err);

//signal.c
void	write_newline(void);
void	prompt_interrupt(void);
int		signal_set(int sig, void *f);

//utils.c
void	print_error(char *str1, char *str2);

#endif
