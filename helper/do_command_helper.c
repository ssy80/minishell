/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:28:32 by ssian             #+#    #+#             */
/*   Updated: 2024/09/28 16:28:37 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void    error_command_is_dir(t_cmd *cmd, t_data *data)
{
    ft_putstr_fd(cmd->cmd, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd("Is a directory\n", STDERR_FILENO);
    free_all(data);
    exit(126);
}

void    error_no_command(t_cmd *cmd, t_data *data)
{
    ft_putstr_fd(cmd->cmd, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd("command not found\n", STDERR_FILENO);
    //ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
    free_all(data);
    exit(127);
}

void    error_no_permission(t_cmd *cmd, t_data *data)
{
    ft_putstr_fd(cmd->cmd, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd("Permission denied\n", STDERR_FILENO);
    free_all(data);
    exit(126);
}

void error_no_file(t_cmd *cmd, t_data *data)
{
    ft_putstr_fd(cmd->cmd, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    //ft_putstr_fd("command not found\n", STDERR_FILENO);
    ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
    free_all(data);
    exit(127);
}

void    error_no_env(t_cmd *cmd, t_data *data)
{
    ft_putstr_fd(cmd->cmd, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
    free_all(data);
    exit(EXIT_FAILURE);
}