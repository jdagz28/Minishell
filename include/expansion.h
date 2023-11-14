/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:57:03 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/13 20:59:27 by jdagoy           ###   ########.fr       */
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
