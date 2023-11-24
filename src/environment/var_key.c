/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/11/13 21:08:55 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int key_isvalid(char* str)
{
	char* pos;
	int len;
	int i;

	if (!str)
		return (0);
	pos = ft_strchr(str, '=');
	if (pos)
		len = pos - str;
	else
		len = ft_strlen(str);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return(0);
	i = 0;
	while (i < len)
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return(0);
		i++;
	}
	return (1);
}
