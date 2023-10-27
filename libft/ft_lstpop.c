/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:52:13 by tbarbe            #+#    #+#             */
/*   Updated: 2023/07/11 16:26:29 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstpop(t_list *list, void (*del)(void *), int id)
{
	t_list	*l;
	t_list	*first;
	t_list	*last;

	l = ft_lstget(list, id);
	first = list;
	last = NULL;
	if (!l)
		return (first);
	if (id > 0)
		last = ft_lstget(list, id - 1);
	if (l != ft_lstlast(list))
	{
		if (last)
			last->next = l->next;
		else
			first = l->next;
	}
	else if (!last)
		first = NULL;
	else
		last->next = NULL;
	ft_lstdelone(l, del);
	return (first);
}
