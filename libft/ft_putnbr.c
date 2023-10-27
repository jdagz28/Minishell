/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:30:23 by tbarbe            #+#    #+#             */
/*   Updated: 2022/10/13 12:45:07 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_putabsnbr_fd(unsigned int n, int fd)
{
	if (n > 9)
	{
		ft_putabsnbr_fd(n / 10, fd);
	}
	ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putabsnbr_fd(-n, fd);
	}
	else
	{
		ft_putabsnbr_fd(n, fd);
	}
}

static int	ft_putabsnbr(unsigned int n, int len)
{
	if (n > 9)
	{
		len = ft_putabsnbr(n / 10, len + 1);
	}
	ft_putchar(n % 10 + '0');
	return (len);
}

int	ft_putnbr(int n)
{
	if (n >= 0)
		return (ft_putabsnbr(n, 1));
	ft_putchar('-');
	return (ft_putabsnbr(-n, 2));
}

int	ft_putunbr(int n)
{
	if (n >= 0)
		return (ft_putabsnbr(n, 1));
	else
		return (ft_putabsnbr(UINT_MAX + n + 1, 1));
}
