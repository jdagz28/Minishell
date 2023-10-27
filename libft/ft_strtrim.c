/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:30:23 by tbarbe            #+#    #+#             */
/*   Updated: 2022/10/13 13:04:22 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	while (s1[begin] && ft_strchr(set, (int)s1[begin]))
		begin++;
	if (ft_strlen(s1) == 0)
		end = 0;
	else
	{
		end = ft_strlen(s1) - 1;
		while (end > begin && ft_strchr(set, (int)s1[end]))
			end--;
		end += 1;
	}
	str = malloc(sizeof(char) * (end - begin + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[begin], end - begin + 1);
	return (str);
}
