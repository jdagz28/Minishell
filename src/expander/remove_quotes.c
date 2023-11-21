/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:22:23 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/20 23:11:09 by jdagoy           ###   ########.fr       */
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
	//!if (str == NULL)
	//! fatal error
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

static void	restore_quotes(char *str)
{
	while (*str != '\0')
	{
		if (*str < 0)
			*str *= -1;
		str++;
	}
}

void	change_quote_state(char quote, bool *in_squote, bool *in_dquotes)
{
	if (quote == '\'' && *in_dquotes == false)
		*in_squote = (*in_squote == false);
	else if (quote == '\"' && *in_squote == false)
		*in_dquotes = (*in_dquotes == false);
}

static int	get_len_without_quotes(char *str)
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

static char	*remove_quotes(char *str)
{
	bool	in_squotes;
	bool	in_dquotes;
	int		i;
	int		j;
	char	*without_quotes;

	in_squotes = false;
	in_dquotes = false;
	i = 0;
	j = 0;
	without_quotes = ft_calloc(get_len_without_quotes(str) + 1, \
									sizeof(*without_quotes));
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' && in_dquotes == false) \
			|| (str[i] == '\"' && in_squotes == false))
			change_quote_state(str[i], &in_squotes, &in_dquotes);
		else
			without_quotes[j++] = str[i];
		++i;
	}
	restore_quotes(without_quotes);
	return (without_quotes);
}

void	remove_quotes_arg(char **argv)
{
	char	*tmp;

	tmp = remove_quotes(*argv);
	free(*argv);
	*argv = tmp;
}
