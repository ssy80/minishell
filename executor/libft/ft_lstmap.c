/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:52:49 by ssian             #+#    #+#             */
/*   Updated: 2024/05/23 14:28:15 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*t;
	t_list	*node;
	void	*value;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	t = NULL;
	while (lst != NULL)
	{
		value = f(lst->content);
		node = ft_lstnew(value);
		if (node == NULL)
		{
			del(value);
			ft_lstclear(&t, del);
			return (NULL);
		}
		ft_lstadd_back(&t, node);
		lst = lst->next;
	}
	return (t);
}
