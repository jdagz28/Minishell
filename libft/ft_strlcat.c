/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:46:22 by tbarbe            #+#    #+#             */
/*   Updated: 2022/10/13 12:56:30 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	if (!src || dstsize <= 0)
		return (ft_strlen(src) + dstsize);
	dst_len = ft_strlen(dst);
	if (dstsize < 1 || dst_len >= dstsize)
		return (ft_strlen(src) + dstsize);
	i = 0;
	while (src[i] && i < dstsize - dst_len -1)
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = 0;
	return (ft_strlen(src) + dst_len);
}
