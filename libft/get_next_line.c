/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:34:35 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 12:35:30 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_strchrpos(char *str, char c)
{
	int		i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char	*buf_transfer(char *str, char *buf, int len)
{
	char	*res;
	int		lastlen;
	int		newlen;
	int		dif;

	lastlen = ft_strlen(str);
	newlen = lastlen + len;
	if (newlen == 0)
		return (NULL);
	res = malloc(sizeof(char) * (newlen + 1));
	if (!res)
		return (NULL);
	dif = BUFFER_SIZE - len;
	ft_strncpy(res, str, lastlen);
	ft_strncpy(&res[lastlen], buf, len);
	ft_strncpy(buf, &buf[len], dif);
	ft_strncpy(&buf[dif], NULL, len);
	if (str)
		free(str);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	int			len;
	int			pos;
	int			r;
	char		*res;

	res = NULL;
	r = 1;
	while (r > 0)
	{
		len = ft_strlen(buf);
		pos = ft_strchrpos(buf, '\n');
		if (pos >= 0)
			len = pos + 1;
		res = buf_transfer(res, buf, len);
		if (pos >= 0)
			return (res);
		r = read(fd, buf, BUFFER_SIZE);
	}
	return (res);
}
