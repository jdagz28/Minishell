/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:52:13 by tbarbe            #+#    #+#             */
/*   Updated: 2023/07/11 16:24:44 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstget(t_list *list, int id)
{
	int	i;

	i = 0;
	while (list && i <= id)
	{
		if (i == id)
			return (list);
		list = list->next;
		i++;
	}
	return (NULL);
}

int	ft_lstget_pos(t_list *lst, void *content)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->content == content)
			return (i);
		lst = lst->next;
		i++;
	}
	return (-1);
}
