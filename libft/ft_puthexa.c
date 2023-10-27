/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c          vvv                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:30:23 by tbarbe            #+#    #+#             */
/*   Updated: 2022/10/27 13:13:52 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_puthexa(unsigned long n, int upper, int len)
{
	int	m;
	int	inc;
	int	l;

	l = len;
	m = n % 16;
	if (upper)
		inc = 'A';
	else
		inc = 'a';
	if (n > 15)
		l = ft_puthexa(n / 16, upper, len + 1);
	if (m > 9)
		ft_putchar(m - 10 + inc);
	else
		ft_putchar(m + '0');
	return (l);
}

int	ft_putptr(void *p)
{
	unsigned long	v;

	v = (unsigned long)p;
	ft_putstr("0x");
	if (!p)
		return (ft_putchar('0') + 2);
	else
		return (ft_puthexa(v, 0, 1) + 2);
}
