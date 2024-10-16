/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:22:46 by ssian             #+#    #+#             */
/*   Updated: 2024/05/23 14:26:22 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
/*head = ft_lstnew(a); &head is a address to 
  pointer that point to another pointer object (t_list) */
/*int main(void)
{
	t_list *head;
	char a[]="hello42";
	head = ft_lstnew(a);
	t_list *new;
	char b[] = "singapore";
	new = ft_lstnew(b);
	ft_lstadd_front(&head, &new);
	printf("1st: %s\n", (char *)new->content);
	printf("2nd: %s\n", (char *)new->next->content);

	//fn();
}*/
