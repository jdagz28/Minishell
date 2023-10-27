/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:30:23 by tbarbe            #+#    #+#             */
/*   Updated: 2023/07/11 16:17:31 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_intlist_getvalue(void *addr)
{
	int	*value;

	value = (int *)addr;
	return (*value);
}

int	ft_intlst_issorted(t_list **lst, int size, int dir)
{
	t_list	*l;
	int		*a;
	int		*b;
	int		i;

	l = *lst;
	i = 0;
	while (l && l->next && i < size)
	{
		a = (int *)l->content;
		b = (int *)l->next->content;
		if ((dir == 1 && *a > *b) || (dir == 0 && *a < *b))
			return (0);
		l = l->next;
		i++;
	}
	return (1);
}

int	ft_intlst_getmin(t_list *lst, int size)
{
	int	i;
	int	id;
	int	*min;

	if (!lst)
		return (-1);
	id = 0;
	min = (int *)lst->content;
	lst = lst->next;
	i = 1;
	while (lst && i < size)
	{
		if (*(int *)lst->content < *min)
		{
			min = (int *)lst->content;
			id = i;
		}
		lst = lst->next;
		i++;
	}
	return (id);
}

t_list	**ft_intlst_sort(t_list **lst)
{
	t_list	**res;
	t_list	**copy;
	t_list	*el;
	int		id;

	if (!lst)
		return (NULL);
	res = malloc(sizeof(t_list *));
	*res = NULL;
	copy = ft_lstcopy(*lst);
	while (*copy)
	{
		id = ft_intlst_getmin(*copy, ft_lstsize(*copy));
		el = ft_lstget(*copy, id);
		ft_lstadd_back(res, ft_lstnew(el->content));
		*copy = ft_lstpop(*copy, NULL, id);
	}
	ft_lstclear(copy, NULL);
	free(copy);
	return (res);
}
