/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstremove_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:58:50 by ssian             #+#    #+#             */
/*   Updated: 2024/06/29 12:05:00 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	lstremove_last(t_list **lst)
{
	t_list *tmp;

	tmp = *lst;
	if (lst == NULL)
		return ;
	if (ft_lstsize(tmp) == 1)
		(*lst) = NULL;
	else if (ft_lstsize(tmp) > 1)
	{
		while (tmp->next->next != NULL)
			tmp = tmp->next;
		tmp->next = NULL;
	}
}