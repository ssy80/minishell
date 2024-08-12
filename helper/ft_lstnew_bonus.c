/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:15:02 by yoong             #+#    #+#             */
/*   Updated: 2024/04/15 05:15:04 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ans;

	ans = malloc(sizeof(t_list));
	if (!ans)
		return (NULL);
	ans->content = content;
	ans->next = NULL;
	return (ans);
}
