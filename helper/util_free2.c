/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_free2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:37:35 by ssian             #+#    #+#             */
/*   Updated: 2024/09/13 14:37:38 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void free_pidt(pid_t *pidt);
void free_pipefd_all(int **pipefd, int size);
void free_charchar_str(char **str);

void free_pidt(pid_t *pidt)
{
    if (pidt != NULL)
    {
        free(pidt);
        pidt = NULL;
    }
}

void free_pipefd_all(int **pipefd, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        free(pipefd[i]);
        i++;
    }
    free(pipefd);
}

void free_charchar_str(char **str)
{
    int i;

    if (str == NULL)
        return ;
    else
    {
        i = 0;
        while (str[i])
        {
            free(str[i]);
            i++;
        }
        free(str);
        str = NULL;
    }
}

void	ft_freelist(t_list *lst)                  //may need update
{
	t_list	*tmp_lst;

	if (lst == NULL)
		return ;
	while (lst != NULL)
	{
		tmp_lst = lst;
		lst = lst->next;
		free(tmp_lst);
	}
	tmp_lst = NULL;
}



