/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_free3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:26:20 by ssian             #+#    #+#             */
/*   Updated: 2024/09/29 16:26:22 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void free_inoutlist(t_list *inout_list)
{
    t_inout *inout;
   
    while (inout_list != NULL)
    {
        inout = (t_inout *)(inout_list->content);
        free_inout(inout);
        inout = NULL;
        inout_list = inout_list->next;
    }
}

void free_inout(t_inout *inout)
{
    if (inout != NULL)
    {
        free(inout->heredoc);
        free(inout);
        inout = NULL;
    }
}

