/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:29:20 by ssian             #+#    #+#             */
/*   Updated: 2024/05/23 14:27:10 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*t;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		t = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = t;
	}
	*lst = NULL;
	lst = NULL;
}
