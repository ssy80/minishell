/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command_mid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:18:11 by ssian             #+#    #+#             */
/*   Updated: 2024/09/27 23:18:14 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static  void close_pipes(int pipe1, int pipe2)
{
    close(pipe1);
    close(pipe2);
}

void    do_command_mid(t_cmd *cmd, int pipefd_in[], int pipefd_out[], pid_t pidt, t_data *data)  
{
    pidt = fork();
    if (pidt == -1)
        error_fork(data); 
    if (pidt == 0) 
    {
        close(pipefd_in[1]);
        close(pipefd_out[0]);
        dup2(pipefd_in[0], STDIN_FILENO);
        close(pipefd_in[0]);
        dup2(pipefd_out[1], STDOUT_FILENO);
        close(pipefd_out[1]);
        if (cmd->inout_list != NULL)
            do_inout(cmd->inout_list, data);
        if (cmd->cmd != NULL)
        {
            if (is_builtin_fn(cmd->cmd) == 1)
                do_builtin(cmd, data);
            else
                do_command(cmd, data);
        }
        free_all(data);
        exit(EXIT_SUCCESS);
    }
    else
        close_pipes(pipefd_in[0], pipefd_in[1]);
}