/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:36:11 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/14 13:47:03 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

int	get_len_var_name(char *argv)
{
	int	len;

	len = 0;
	while ((ft_isalnum(argv[len]) != 0 || argv[len] == '_') \
				&& argv[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*get_var_name(char *argv)
{
	int		i;
	int		j;
	char	*var_name;

	i = 1;
	j = 0;
	var_name = ft_calloc(get_len_var_name(argv + i) + 1, sizeof(*var_name));
	//! if (var_name == NULL)
	//! 	//fatal_error		
	while ((ft_isalnum(argv[i]) != 0 || argv[i] == '_') && argv[i] != '\0')
	{
		var_name[j] = argv[i];
		++i;
		++j;
	}
	var_name[j] = '\0';
	// printf("var_name: %s\n",var_name);
	return (var_name);
}

void	get_var_name_value(char *argv, char **var_name, char **var_value)
{
	if (*(argv + 1) == '?')
	{
		*var_name = ft_strdup("?");
		*var_value = ft_strdup("test"); //!ft_itoa(*get_exit_value());
	}
	else
	{
		*var_name = get_var_name(argv);
		*var_value = reverse_quotes(getenv(*var_name));
		// printf("var name: %s\n", *var_name);
		// printf("var value: %s\n", getenv(*var_name));
		if (*var_value == NULL)
			*var_value = "";
	}
}
