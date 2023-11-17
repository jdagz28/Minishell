/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:05:08 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/17 10:21:39 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_del(char const *s1, char const *s2, char const *sep)
{
	int		size;
	char	*new_str;

	if (!s1)
	{
		if (!s2)
			return (NULL);
		return (ft_strjoin_del(sep, s2, ""));
	}
	if (s2)
		return (ft_strjoin_del(s1, sep, ""));
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(sep);
	if (s1[0] == '\0' && s2[0] == '\0')
		return (ft_strdup(""));
	new_str = malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, (char *)s1, ft_strlen(new_str) + ft_strlen(s1));
	ft_strlcat(new_str, (char *)sep, ft_strlen(new_str) + ft_strlen(sep));
	ft_strlcat(new_str, (char *)s2, ft_strlen(new_str) + ft_strlen(s2));
	return (new_str);
}
