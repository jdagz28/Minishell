/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:52:13 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 12:37:39 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_stradd(char *beg, char *end)
{
	char	*res;
	int		len;
	int		beglen;
	int		endlen;

	beglen = ft_strlen(beg);
	endlen = ft_strlen(end);
	len = beglen + endlen;
	if (len == 0)
		return (NULL);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strncpy(res, beg, beglen);
	ft_strncpy(&res[beglen], end, endlen);
	if (beg)
		free(beg);
	return (res);
}
