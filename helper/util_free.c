/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:43:18 by ssian             #+#    #+#             */
/*   Updated: 2024/09/11 14:43:21 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void free_cmd_cmd(char *cmd)
{
    if (cmd != NULL)
        free(cmd);
    cmd = NULL;
}

void free_cmd(t_cmd *cmd)
{
    if (cmd != NULL)
    {
        free_cmd_args(cmd->args);
        free_inoutlist(cmd->inout_list);
    }
    cmd = NULL;
}

void free_cmd_args(char **args)
{
    if (args == NULL)
        return ;
    else
    {
        free(args);
        args = NULL;
    }
}

void free_cmdlist(t_list *cmd_list)
{
    t_cmd	*cmd;
  
    while (cmd_list != NULL)
	{
		cmd = (t_cmd *)(cmd_list->content);
        free_cmd_args(cmd->args);
        free_inoutlist(cmd->inout_list);
        ft_freelist(cmd->inout_list);
        free(cmd);
        cmd = NULL;
		cmd_list = cmd_list->next;
	}
}

void	free_datacmd(t_data *data)
{
	int	i;

	i = 0;

    while (i < data->itr)
    {
        free(data->cmd[i]);
        data->cmd[i] = NULL;
        i++;
    }
}