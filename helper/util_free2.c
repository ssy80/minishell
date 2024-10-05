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
        pipefd[i] = NULL;
        i++;
    }
    free(pipefd);
    pipefd = NULL;
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

void free_all(t_data *data)
{
    free_pidt(data->pidt);
    free_pipefd_all(data->pipefd, ft_lstsize(data->cmd_list) - 1);
    free_cmdlist(data->cmd_list);
    ft_freelist(data->cmd_list);
    free_datacmd(data);
    freenullall(data);
}

void free_all2(t_data *data)
{
    free_cmdlist(data->cmd_list);
    ft_freelist(data->cmd_list);
    free_datacmd(data);
    freenullall(data);
}