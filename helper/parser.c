/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:45:34 by ssian             #+#    #+#             */
/*   Updated: 2024/08/14 16:45:37 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

/*check for operator < and shift to the front of the list*/
void parse_token_list(t_list **token_list)
{
    t_list *lst;
    t_list *tmp;
    t_list *tmp_list;
    int     i;
    t_token *token;
    int     size;

    tmp = NULL;
    tmp_list = NULL;
    size = 0;
    lst = *token_list;
//print_token_list(lst);
    i = 0;
    while (lst->next != NULL)
    {
        token = (t_token *)(lst->next->content);
        if (token->type == 2) //2 for operator
        {
            if (equals(token->operator, "<") && i != 0)
            {
                //tmp point to '<' node end with + 1 node or none
                tmp = lst->next;
                
              

                if (lst->next->next == NULL)
                {
                    //printf("tmp->next == NULL\n");
                    lst->next = NULL;
                }
                else if (lst->next->next->next != NULL)
                    lst->next = lst->next->next->next;
                else
                    lst->next = NULL;

                
                

                //ft_lstadd_back(&tmp_list, tmp->next);
                //ft_lstadd_back(&tmp_list, tmp);
                //size = ft_lstsize(tmp);
                //printf("size: %d\n", size);
                

                //printf("tmp: %s\n", ((t_token *)(tmp->content))->operator);
            
                if (tmp->next != NULL)
                {
                    if (tmp->next->next != NULL)
                        tmp->next->next = NULL;
                }
                if (tmp_list == NULL)
                    tmp_list = tmp;
                else 
                    ft_lstlast(tmp_list)->next  = tmp;
                printf("----\n");
                print_token_list(tmp_list);
                printf("----\n");
                print_token_list(*token_list);

                //move to the front
                size = ft_lstsize(tmp);
                printf("size: %d\n", size);
                /*if (size == 1)
                {
                    ft_lstadd_front(token_list, ft_lstlast(tmp));
                }
                if (size == 2)
                {
                    ft_lstadd_front(token_list, ft_lstlast(tmp));
                    ft_lstadd_front(token_list, tmp);
                }*/

               // print_token_list(*token_list);
               // lst = *token_list;
                continue ;
               // break;
            }
        }
        i++;
        lst = lst->next;
    }

    if (tmp_list != NULL)
    {
        lst = *token_list;
        ft_lstlast(tmp_list)->next  = lst;
        *token_list = tmp_list;
    }
}