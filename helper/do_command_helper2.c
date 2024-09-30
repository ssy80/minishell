/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command_helper2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:18:58 by ssian             #+#    #+#             */
/*   Updated: 2024/09/30 13:19:03 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void    error_execve(t_cmd *cmd, t_data *data)
{
    perror(cmd->cmd);
    free_all(data);
    if (errno == 2)
        exit(127);
    else
        exit(EXIT_FAILURE);
}

