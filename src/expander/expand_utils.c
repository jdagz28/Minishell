/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:58:00 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/14 03:15:23 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

bool	check_valid_expansion(int i, char ***splitted_var, char **argv)
{
	if (i > 0 && ft_arraylen(*splitted_var) > 1 \
			&& is_redirect(argv[i - 1]) == true)
	{
		print_error(argv[i], "ambigous redirect");
		free((void **)splitted_var);
		return (false);
	}
	return (true);
}

bool	next_char(char c)
{
	return (c == '\0' || ((ft_isalnum(c) == 0 && c != '_') && c != '?'));
}

int	ft_arraylen(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

char	*get_after_var(char *str, int index_dollar)
{
	char	*ptr;

	ptr = str + index_dollar + 1;
	while (ft_isalnum(*ptr) == 1 || *ptr == '_')
		ptr++;
	return (ptr);
}

bool	has_space(char *str)
{
	while (*str != '\0')
		if (ft_isspace(*(str++)))
			return (true);
	return (false);
}
