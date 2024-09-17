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

//? check malloc
//? check open error
//? check exec error
//? command not found
//? EXIT_SUCCCESS
//? EXIT_ERROR

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
    //ft_freelist(cmd_list);
    cmd_list = NULL;
}

void free_inoutlist(t_list *inout_list)
{
    t_inout *inout;
    //t_list *tmp;

    //tmp = inout_list;
    while (inout_list != NULL)
    {
        inout = (t_inout *)(inout_list->content);
        free_inout(inout);
        inout = NULL;
        inout_list = inout_list->next;
    }
    //ft_freelist(tmp);
    //tmp = NULL; 
    //inout_list = NULL;
}

void free_inout(t_inout *inout)
{
    if (inout != NULL)
    {
        free(inout->heredoc);
        free(inout);
        inout = NULL;
    }
}


void	free_datacmd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->itr)
	{
        if (data->cmd[i] != NULL)
        {
            free(data->cmd[i]);
            data->cmd[i] = NULL;
        }
        i++;
	}
}