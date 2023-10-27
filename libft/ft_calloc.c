/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:52:13 by tbarbe            #+#    #+#             */
/*   Updated: 2022/10/13 12:26:44 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	i;

	p = malloc(size * count);
	i = 0;
	if (!p)
		return (p);
	while (i < size * count)
	{
		p[i] = 0;
		i++;
	}
	return ((void *)p);
}
