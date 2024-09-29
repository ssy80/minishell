/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command_first.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:04:34 by ssian             #+#    #+#             */
/*   Updated: 2024/09/27 23:04:39 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void    do_command_first(t_cmd *cmd, int pipefd_out[], pid_t pidt, t_data *data)
{
    pidt = fork();
    if (pidt == -1) 
        error_fork(data);
    if (pidt == 0) 
    {
        close(pipefd_out[0]);
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
}