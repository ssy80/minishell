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

static void    process_cmd(t_list *cmd_list, int size, t_data *data)
{
    if (size == 1)
        do_single_cmd(data);
    else if (size > 1)
        do_multiple_command(cmd_list, size, data);
}

static void free_pidt_pipe(pid_t *pidt, int **pipefd, int size)
{
    free_pidt(pidt);
    free_pipefd_all(pipefd, size);
}

int process_cmd_list(t_list *cmd_list, t_data *data)
{
    int     **pipefd;
    pid_t   *pidt;
    int     size;
    int     heredoc_status;

    //init_pipe_pid(pidt, pipefd, data);
    data->pipefd = NULL;
    data->pidt = NULL;
    /*pipefd = NULL;
    pidt = NULL;
    data->pipefd = pipefd;
    data->pidt = pidt;*/
    //if (process_heredoc(cmd_list, data) <= 0)     //SIGINT termination -9    0 = malloc failed, some fatal error, dont continue
    //    return(0);
    heredoc_status = do_heredoc(cmd_list, data);
    if (heredoc_status <= 0)                               
        return (heredoc_status);
    size = ft_lstsize(cmd_list);
    if (size > 0)
    {
        //if (init_pipe_pid(pidt, pipefd, size) == 0)
        //    return (0);
        pipefd = get_pipe(size - 1);
        if (pipefd == NULL)
            return (0);
        pidt = get_pidt(size);
        if (pidt == NULL)
            return (0);
        data->pipefd = pipefd;
        data->pidt = pidt;
    }
    //else
    //{
    //    pipefd = NULL;
    //    pidt = NULL;
    //}
    //data->pipefd = pipefd;
    //data->pidt = pidt;
    
    process_cmd(cmd_list, size, data);

    /*if (size == 1)
        do_single_cmd(data);
    else if (size > 1)
        do_multiple_command(cmd_list, size, data);
    */
    return (free_pidt_pipe(pidt, pipefd, size - 1), 1);
}