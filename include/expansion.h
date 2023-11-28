/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:57:03 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/28 14:10:31 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "minishell.h"

typedef struct s_expand
{
	int		len_old_argv;
	int		len_argv_to_add;
	int		len_new_argv;
	bool	first_join;
	bool	last_join;
	bool	has_space;
	int		i_old;
	int		i_new;
	int		i_split;
	int		index_dollar;
}	t_expand;

typedef struct s_expandvar
{
	char			**cmd_argv;
	int				j;
	char			*new_word;
	int				i;
	bool			dou_quotes;
	bool			sin_quotes;
	t_simple_cmd	*cmd;
}	t_expandvar;

//checktab_for_var.c
bool	checktab_for_var(char **tab, char *var_name);

//expand_cmds.c
bool	expand_cmds(t_node *ast, t_shell *shell);

//expand_replace_var_value.c
char	*replace_varval(char **argv, int len_varname, int i, \
				char *var_value);

//expand_utils.c
bool	check_valid_expansion(int i, char ***splitted_var, char **argv);
bool	next_char(char c);
char	*get_after_var(char *str, int index_dollar);
bool	has_space(char *str);

//expand_var_realloc_argv.c
bool	realloc_argv(t_simple_cmd *cmd, int const i, int *j, \
							char *var_value);

//expand_var_utils.c
void	append_char(char **s, char c);
void	init_expandvar(t_expandvar *params, int const i, t_simple_cmd *cmd);
int		get_len_var_name(char *argv);
char	*get_var_name(char *argv);
void	get_var_name_value(char *argv, char **var_name, \
							char **var_value, t_shell *shell);

//expand_vars.c
bool	expand_vars(t_simple_cmd *cmd, int const i, t_shell *shell);

//expand_vars_heredoc.c
void	expand_vars_heredoc(char **argv, t_shell *shell);

//remove_quotes_uitls.c
char	*reverse_quotes(char *var_value);
void	change_quote_state(char quote, bool *in_squote, bool *in_dquotes);
int		get_len_without_quotes(char *str);

//remove_quotes.c
void	remove_quotes_arg(char **argv);

//free_array.c
void	free_array(char ***array);

#endif