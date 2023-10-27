/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:30:23 by tbarbe            #+#    #+#             */
/*   Updated: 2022/10/13 12:33:33 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*last;
	t_list	*next;

	if (!lst || !*lst)
		return ;
	last = *lst;
	while (last)
	{
		next = last->next;
		ft_lstdelone(last, del);
		last = next;
	}
	*lst = NULL;
}
