/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:30:08 by tbarbe            #+#    #+#             */
/*   Updated: 2022/10/13 13:10:33 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	l;
	int		i;
	char	*pos;

	l = c;
	i = 0;
	pos = NULL;
	while (s[i])
	{
		if (s[i] == l)
			pos = (char *)&s[i];
		i++;
	}
	if (l == 0)
		pos = (char *)&s[i];
	return (pos);
}
