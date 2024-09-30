/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_multiple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:04:08 by ssian             #+#    #+#             */
/*   Updated: 2024/09/28 12:04:11 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"


static void error_pipe(t_data *data)
{
    perror("pipe create failed!");
    free_all(data);      
    exit(EXIT_FAILURE);
}

static void wait_process_end(pid_t *pidt, int size, t_data *data)
{
    int i;
    int status;

    i = 0;
	ft_bzero(&status, sizeof(int));
    while (i < size)
    {
        waitpid(pidt[i], &status, 0);
        if (WIFEXITED(status))
            update_exit_status(WEXITSTATUS(status), data);
        i++;
    }
}

void    do_multiple_command(t_list *cmd_list, int size, t_data *data)
{
    int i;
    t_cmd   *cmd;

    i = 0;
    while (cmd_list != NULL)
    {
        cmd = (t_cmd *)(cmd_list->content);

        if (i != (size-1))
        {
            if (pipe(data->pipefd[i]) == -1)
                error_pipe(data);
        }

        if(i == 0)                                                        //first cmd
            do_command_first(cmd, data->pipefd[i], data->pidt[i], data);
        else if (i == (size - 1))                                           //last cmd
            do_command_last(cmd, data->pipefd[i-1], data->pidt[i], data);
        else                                                              //middle cmd
            do_command_mid(cmd, data->pipefd[i-1], data->pipefd[i], data->pidt[i], data);
        cmd_list = cmd_list->next;
        i++;
    }
    wait_process_end(data->pidt, size, data);
}

