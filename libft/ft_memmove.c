/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:34:20 by tbarbe            #+#    #+#             */
/*   Updated: 2022/10/07 18:42:23 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	const char	*s;
	char		*d;

	if (!dst && !src)
		return (dst);
	d = (char *)dst;
	s = src;
	i = 0;
	while (i < len)
	{
		if (dst <= src)
			d[i] = s[i];
		else
			d[len - i - 1] = s[len - i - 1];
		i++;
	}
	return (dst);
}
