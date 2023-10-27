/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:30:23 by tbarbe            #+#    #+#             */
/*   Updated: 2023/07/11 16:23:35 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	**ft_lstcopy(t_list *lst)
{
	t_list	**res;
	t_list	*new;

	if (!lst)
		return (NULL);
	res = malloc(sizeof(t_list **));
	*res = NULL;
	while (lst)
	{
		new = ft_lstnew(lst->content);
		if (!new)
		{
			ft_lstclear(res, NULL);
			free(res);
			return (NULL);
		}
		ft_lstadd_back(res, new);
		lst = lst->next;
	}
	return (res);
}
