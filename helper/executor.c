/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:20:22 by ssian             #+#    #+#             */
/*   Updated: 2024/08/28 16:20:23 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int  process_heredoc(t_list *cmd_list)
{
    t_cmd   *cmd;
    t_list  *inout_list;
    t_inout *inout;
    int     i;

    i = 0;
    while (cmd_list != NULL)
    {
        cmd = (t_cmd *)(cmd_list->content);
        inout_list = cmd->inout_list;
        while (inout_list != NULL)
        {
            inout = (t_inout *)(inout_list->content);
            if (inout->type == 3)                               
            {
                if (do_heredoc(inout, i) == 0)
                    return (0);
            }
            i++;
            inout_list = inout_list->next;
        }
        cmd_list = cmd_list->next;
    }
    return (1);
}

static void free_pidt_pipe(pid_t *pidt, int **pipefd, int size)
{
    free_pidt(pidt);
    free_pipefd_all(pipefd, size);
}

int process_cmd_list(t_list *cmd_list, t_data *data)
{
    int     **pipefd;
    int     size;
    pid_t   *pidt;

    if (process_heredoc(cmd_list) == 0)
        return (0);
    size = ft_lstsize(cmd_list);
    pipefd = get_pipe(size - 1);
    if (pipefd == NULL)
        return (0);
    pidt = get_pidt(size);
    if (pidt == NULL)
        return (0);
    data->pipefd = pipefd;
    data->pidt = pidt;
    if (size == 1)
        do_single_cmd(data);
    else if (size > 1)
        do_multiple_command(cmd_list, size, data);
    return (free_pidt_pipe(pidt, pipefd, size - 1), 1);
}