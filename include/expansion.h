/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:57:03 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/14 03:15:29 by jdagoy           ###   ########.fr       */
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

//expand_cmds.c
bool	expand_cmds(t_node *ast);

//expand_replace_var_value.c
char	*replace_varval(char **argv, int len_varname, int i, \
				char *var_value);

//expand_utils.c
bool	check_valid_expansion(int i, char ***splitted_var, char **argv);
bool	next_char(char c);
int		ft_arraylen(char **array);
char	*get_after_var(char *str, int index_dollar);
bool	has_space(char *str);

//expand_var_realloc_argv.c
bool	realloc_argv(t_simple_cmd *cmd, int const i, int *j, \
							char *var_value);

//expand_vars.c
bool	expand_vars(t_simple_cmd *cmd, int const i);

//remove_quotes
void	change_quote_state(char quote, bool *in_squote, bool *in_dquotes);
void	remove_quotes_arg(char **argv);

#endif