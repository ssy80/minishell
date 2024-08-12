/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:13:13 by yoong             #+#    #+#             */
/*   Updated: 2024/04/15 05:13:15 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cp;

	if (!*lst)
	{
		*lst = new;
		lst[0]->next = NULL;
		return ;
	}
	cp = lst[0];
	while (cp->next != NULL)
		cp = cp->next;
	cp->next = new;
}
