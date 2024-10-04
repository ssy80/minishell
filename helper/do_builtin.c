/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:08:05 by ssian             #+#    #+#             */
/*   Updated: 2024/09/27 23:08:07 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

/* return (1) exit status for error , 0 for success*/
int    do_builtin(t_cmd *cmd, t_data *data)
{
    if (equals(cmd->cmd, "echo") == 1)
        builtin_echo(cmd->args);
    else if (equals(cmd->cmd, "cd") == 1)
    {
        if (builtin_cd(cmd->args, data) == 0)
            return (1);
    }
    else if (equals(cmd->cmd, "pwd") == 1)
        builtin_pwd();
    else if (equals(cmd->cmd, "export") == 1)
    {
        if (builtin_export(cmd->args, data) == 0)
            return (1);
    }
    else if (equals(cmd->cmd, "unset") == 1)
        builtin_unset(cmd->args, data);
    else if (equals(cmd->cmd, "env") == 1)
    {
        if (builtin_get_env(cmd->args, data) == 0)
            return (127);
    }
    else if (equals(cmd->cmd, "exit") == 1)
    {
        if (builtin_exit(cmd->args, data) == 0)
            return (1);
    }
    return (0);
}

