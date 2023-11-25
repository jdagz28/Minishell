/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_realloc_argv.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:00:34 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/25 18:03:16 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

static void	handle_last_join(char *arg, char **new_argv, \
									char **splitted_var, t_expand *utils)
{
	char	*after_var;

	after_var = get_after_var(arg, utils->index_dollar);
	if (utils->last_join == true && *after_var != '\0')
	{
		free((void **)&new_argv[utils->i_new - 1]);
		new_argv[utils->i_new - 1] = \
				ft_strjoin(splitted_var[utils->i_split - 1], after_var);
		if (new_argv[utils->i_new - 1] == NULL)
			return ;
		utils->i_split++;
	}
	else if (*after_var != '\0')
		new_argv[utils->i_new++] = ft_strdup(after_var);
}

static void	handle_first_join(char *arg, char **new_argv, \
								char **splitted_var, t_expand *utils)
{
	char	*before_dollar;

	before_dollar = ft_strndup(arg, utils->index_dollar);
	if (before_dollar == NULL)
		return ;
	if (utils->first_join == true)
	{
		new_argv[utils->i_new] = \
				ft_strjoin(before_dollar, splitted_var[utils->i_split]);
		if (new_argv[utils->i_new] == NULL)
		{
			free(before_dollar);
			return ;
		}
		utils->i_new++;
		utils->i_split++;
		free(before_dollar);
	}
	else if (*before_dollar != '\0')
	{
		new_argv[utils->i_new] = before_dollar;
		utils->i_new++;
	}
	else
		free(before_dollar);
}

static void	init_expand_utils(char **argv, char **splitted_var, \
								char *var_value, t_expand *utils)
{
	utils->has_space = has_space(var_value);
	utils->first_join = (ft_isspace(var_value[0]) == 0);
	utils->last_join = (ft_isspace(var_value[ft_strlen(var_value) - 1]) == 0);
	utils->len_old_argv = ft_arraylen(argv);
	utils->len_argv_to_add = ft_arraylen(splitted_var);
	utils->len_new_argv = utils->len_old_argv + utils->len_argv_to_add \
		- (utils->first_join == false) - (utils->last_join == false) \
		+ (utils->has_space == true);
	utils->i_old = 0;
	utils->i_new = 0;
	utils->i_split = 0;
}

static void	free_array_realloc(char **argv, char **splitted_var)
{
	free_array(&argv);
	free_array(&splitted_var);
	free(splitted_var);
}

bool	realloc_argv(t_simple_cmd *cmd, int const i, int *j, char *var_value)
{
	t_expand	utils;
	char		**new_argv;
	char		**splitted_var;

	splitted_var = ft_split(var_value, ' ');
	if (check_valid_expansion(i, &splitted_var, cmd->argv) == false)
		return (false);
	init_expand_utils(cmd->argv, splitted_var, var_value, &utils);
	utils.index_dollar = *j;
	new_argv = ft_calloc(utils.len_new_argv + 1, sizeof(*new_argv));
	if (new_argv == NULL)
		return (false);
	while (utils.i_new < i)
		new_argv[utils.i_new++] = ft_strdup(cmd->argv[utils.i_old++]);
	handle_first_join(cmd->argv[i], new_argv, splitted_var, &utils);
	while (utils.i_split < utils.len_argv_to_add)
		new_argv[utils.i_new++] = ft_strdup(splitted_var[utils.i_split++]);
	handle_last_join(cmd->argv[i], new_argv, splitted_var, &utils);
	utils.i_old++;
	while (cmd->argv[utils.i_old] != NULL)
		new_argv[utils.i_new++] = ft_strdup(cmd->argv[utils.i_old++]);
	new_argv[utils.i_new] = NULL;
	free_array_realloc(cmd->argv, splitted_var);
	cmd->argv = new_argv;
	return (true);
}
