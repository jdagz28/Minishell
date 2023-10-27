/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:25:29 by tbarbe            #+#    #+#             */
/*   Updated: 2023/03/03 16:08:46 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static unsigned long	ft_checkulmax(unsigned long n)
{
	if (n > UINT_MAX)
		n = UINT_MAX + n + 1;
	return (n);
}

static int	ft_putvalue(char c, va_list app)
{
	if (c == 'c')
		return (ft_putchar(va_arg(app, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(app, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(app, void *)));
	else if (c == 'i' || c == 'd')
		return (ft_putnbr(va_arg(app, int)));
	else if (c == 'u')
		return (ft_putunbr(va_arg(app, int)));
	else if (c == 'x')
		return (ft_puthexa(ft_checkulmax(va_arg(app, int)), 0, 1));
	else if (c == 'X')
		return (ft_puthexa(ft_checkulmax(va_arg(app, int)), 1, 1));
	else if (c == '%')
		return (ft_putchar('%'));
	return (0);
}

static int	check_print(const char *str, va_list app, int i)
{
	int	res;

	res = 0;
	if (ft_strchr("cspdiuxX%", str[i + 1]))
		res += ft_putvalue(str[i + 1], app) - 2;
	else
		res += ft_putchar(str[i + 1]) - 2;
	return (res);
}

int	ft_printf(const char *str, ...)
{
	int			i;
	int			len;
	int			res;
	va_list		app;

	if (!str)
		return (-1);
	len = ft_strlen(str);
	res = len;
	i = 0;
	va_start(app, str);
	while (str[i])
	{
		if (i < len - 1 && str[i] == '%')
			res += check_print(str, app, i++);
		else if (str[i] != '%')
			write(1, &str[i], 1);
		else
			res -= 1;
		i++;
	}
	va_end(app);
	return (res);
}
