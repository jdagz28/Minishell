/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:30:23 by tbarbe            #+#    #+#             */
/*   Updated: 2023/07/11 16:27:07 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l;
	t_list	*new;
	t_list	*map;

	if (!lst || !f || !del)
		return (NULL);
	l = lst;
	map = NULL;
	while (l)
	{
		new = ft_lstnew(f(l->content));
		ft_lstadd_back(&map, new);
		if (!new)
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		l = l->next;
	}
	return (map);
}
