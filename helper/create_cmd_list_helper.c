/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:43:29 by ssian             #+#    #+#             */
/*   Updated: 2024/09/27 11:43:37 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int do_is_inout(t_data *data, t_ccmd *ccmd, int *i)
{
    int inout_type;

    inout_type = is_inout(data->cmd[*i]);
    *i = *i + 1;

    if (add_inout(&(ccmd->inout_list), inout_type, data->cmd[*i]) == 0)
        return (print_error_create_cmdlist(), 0);
    if (*i == (data->itr - 1))
    {
        if (add_cmd(ccmd->command, ccmd->args, ccmd->inout_list, &(ccmd->cmd_list)) == 0)
            return (print_error_create_cmdlist(), 0);
    }
    return (1);
}

/* 0=create(>) 1=append(>>) 2=infile(<) 3=heredoc(<<) */
int add_inout(t_list **inout_list, int inout_type, char *inout_value)
{
    t_inout *inout;
    t_list *inout_node;

    inout = NULL;
    inout_node = NULL;
    if (inout_type == 0)
        inout = create_inout(inout_type, inout_value, NULL, NULL); 
    else if (inout_type == 1)
        inout = create_inout(inout_type, inout_value, NULL, NULL); 
    else if (inout_type == 2)
        inout = create_inout(inout_type, inout_value, NULL, NULL); 
    else if (inout_type == 3)
        inout = create_inout(inout_type, NULL, NULL, inout_value); 
    if (inout == NULL)
        return (0); 
    inout_node = ft_lstnew(inout);
    if (inout_node == NULL)
    {
        free_inout(inout);
        return (0);
    }
    ft_lstadd_back(inout_list, inout_node);
    return (1);
}

int add_cmd(char *command, char **args, t_list *inout_list, t_list **cmd_list)
{
    t_cmd	*cmd;
    t_list *cmd_node;

    cmd = NULL;
    cmd_node = NULL;
    if (args == NULL)
    {
        args = get_null_args();
        if (args == NULL) 
            return (0);
    }
    cmd = create_cmd(command, args, inout_list);
    if (cmd == NULL)
        return (free_charchar_str(args), 0);
    cmd_node = ft_lstnew(cmd);	
    if (cmd_node == NULL)
    {   
        free_charchar_str(args);
        free_cmd(cmd);
        return (0);
    }                
    ft_lstadd_back(cmd_list, cmd_node);
    return (1);
}

t_cmd   *create_cmd(char *command, char **args, t_list *inout_list)
{
    t_cmd 	*cmd;

    cmd = malloc(sizeof(t_cmd));
    if (cmd == NULL)
        return (NULL);
    cmd->cmd = command;
    cmd->args = args;
    cmd->inout_list = inout_list;
    return (cmd);
}

t_inout *create_inout(int type, char *file, char *heredoc, char *delimiter)
{
    t_inout *inout;

    inout = malloc(sizeof(t_inout));
    if (inout == NULL)
        return (NULL);
    inout->type = type;
	inout->file = file;
	inout->heredoc = heredoc;
	inout->delimiter = delimiter;
    return (inout);
}