/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:22:23 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/21 20:07:16 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

char	*reverse_quotes(char *var_value)
{
	char	*str;
	int		i;

	if (var_value == NULL)
		return (NULL);
	i = 0;
	str = ft_calloc(ft_strlen(var_value) + 1, sizeof(*str));
	if (str == NULL)
		return (NULL);
	while (var_value[i] != '\0')
	{
		if (var_value[i] == '\'' || var_value[i] == '\"')
			str[i] = -var_value[i];
		else
			str[i] = var_value[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	change_quote_state(char quote, bool *in_squote, bool *in_dquotes)
{
	if (quote == '\'' && *in_dquotes == false)
		*in_squote = (*in_squote == false);
	else if (quote == '\"' && *in_squote == false)
		*in_dquotes = (*in_dquotes == false);
}

int	get_len_without_quotes(char *str)
{
	bool	in_squotes;
	bool	in_dquotes;
	int		i;
	int		len;

	in_squotes = false;
	in_dquotes = false;
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' && in_dquotes == false) \
			|| (str[i] == '\"' && in_squotes == false))
			change_quote_state(str[i], &in_squotes, &in_dquotes);
		else
			len++;
		i++;
	}
	return (len);
}
