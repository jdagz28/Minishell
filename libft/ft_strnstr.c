/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:30:08 by tbarbe            #+#    #+#             */
/*   Updated: 2022/10/13 13:02:50 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (ft_strlen(needle) == 0 || haystack == needle)
		return ((char *)haystack);
	if (len > ft_strlen(haystack))
		len = ft_strlen(haystack);
	if (len <= 0 || ft_strlen(needle) > len)
		return (NULL);
	i = 0;
	while (i + ft_strlen(needle) <= len)
	{
		if (ft_strncmp(&haystack[i], needle, ft_strlen(needle)) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
