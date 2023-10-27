/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:52:13 by tbarbe            #+#    #+#             */
/*   Updated: 2022/10/13 13:05:06 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	l;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		l = 0;
	else
	{
		l = ft_strlen(&s[start]);
		if (l > len)
			l = len;
	}
	str = malloc(sizeof(char) * (l + 1));
	if (!str)
		return (NULL);
	i = start;
	while (i < l + start && s[i])
	{
		str[i - start] = s[i];
		i++;
	}
	str[i - start] = 0;
	return (str);
}
