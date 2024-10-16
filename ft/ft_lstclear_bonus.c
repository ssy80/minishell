/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:13:38 by yoong             #+#    #+#             */
/*   Updated: 2024/04/15 05:13:41 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*np;

	if (!lst || !lst[0] || !del)
		return ;
	np = lst[0]->next;
	del(lst[0]->content);
	free(*lst);
	*lst = NULL;
	ft_lstclear(&np, del);
}
