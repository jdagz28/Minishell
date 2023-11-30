/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:30:08 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/30 15:33:44 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	void	*res;

	res = (void *)s;
	i = 0;
	while (i < n)
	{
		if (*(int *)res == c)
			return (res);
		res += sizeof(char);
		i++;
	}
	return (NULL);
}
