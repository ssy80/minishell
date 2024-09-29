/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_single_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:44:00 by ssian             #+#    #+#             */
/*   Updated: 2024/09/27 22:44:03 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void do_in_child(t_cmd *cmd, t_data *data)
{
    if (cmd->inout_list != NULL)
        do_inout(cmd->inout_list, data);
    if (cmd->cmd != NULL)
    {
        if (is_builtin_fn(cmd->cmd) == 1)
        {
            if(equals(cmd->cmd, "env") == 1)
                builtin_get_env(cmd->args, data);
            else if (equals(cmd->cmd, "pwd") == 1)
                getpwd();
            else if (equals(cmd->cmd, "echo") == 1)
                builtin_echo(cmd->args);
        }
        else
            do_command(cmd, data);
    }
    free_all(data);        
    exit(EXIT_SUCCESS);
}

static void do_in_parent(t_cmd *cmd, t_data *data)
{
    if(equals(cmd->cmd, "export") == 1)
        builtin_export(cmd->args, data);
    else if(equals(cmd->cmd, "unset") == 1)
        builtin_unset(cmd->args, data);
    else if(equals(cmd->cmd, "cd") == 1)
        builtin_cd(cmd->args, data);
    else if(equals(cmd->cmd, "exit") == 1)
        builtin_exit(cmd->args, data);
}

void    do_single_cmd(t_data *data)
{
    pid_t pidt;
    int status;
    t_cmd   *cmd;

    cmd = (t_cmd *)(data->cmd_list->content); 
    pidt = fork();
    if (pidt == -1) 
    {
        perror("fork failed!");
        free_all(data);    
        exit(EXIT_FAILURE);
    }

    if (pidt == 0)
    {
        do_in_child(cmd, data);
    }
    else
    {
        do_in_parent(cmd, data);
        wait(&status);
        if (WIFEXITED(status))
            update_exit_status(WEXITSTATUS(status), data);

    }
}