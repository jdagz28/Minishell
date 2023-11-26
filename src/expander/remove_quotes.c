/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:06:22 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/25 17:55:02 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expansion.h"

static void	restore_quotes(char *str)
{
	while (*str != '\0')
	{
		if (*str < 0)
			*str *= -1;
		str++;
	}
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
	if (without_quotes == NULL)
		return (NULL);
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
