/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 10:36:11 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/21 20:04:09 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = malloc(size);
	if (new == NULL)
		return ;
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

void	init_expandvar(t_expandvar *params, int const i, t_simple_cmd *cmd)
{
	params->cmd_argv = cmd->argv;
	params->j = 0;
	params->new_word = NULL;
	params->dou_quotes = false;
	params->sin_quotes = false;
	params->cmd = cmd;
	params->i = i;
}

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
	if (var_name == NULL)
		return (NULL);
	while ((ft_isalnum(argv[i]) != 0 || argv[i] == '_') && argv[i] != '\0')
	{
		var_name[j] = argv[i];
		++i;
		++j;
	}
	var_name[j] = '\0';
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
		if (*var_value == NULL)
			*var_value = "";
	}
}
