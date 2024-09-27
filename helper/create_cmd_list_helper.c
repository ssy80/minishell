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

int add_inout(t_list **inout_list, int inout_type, char *inout_value)
{
    t_inout *inout;
    t_list *inout_node;

    inout = NULL;
    inout_node = NULL;
    if (inout_type == 0)                                                     //0=create(>)
        inout = create_inout(inout_type, inout_value, NULL, NULL); 
    else if (inout_type == 1)                                                //1=append(>>)
        inout = create_inout(inout_type, inout_value, NULL, NULL); 
    else if (inout_type == 2)                                                //2=infile(<)
        inout = create_inout(inout_type, inout_value, NULL, NULL); 
    else if (inout_type == 3)                                                //3=heredoc(<<)
        inout = create_inout(inout_type, NULL, NULL, inout_value); 

    if (inout == NULL)                                                       //malloc failed?
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
        if (args == NULL)                          //malloc failed?  
            return (0);
    }

    cmd = create_cmd(command, args, inout_list);
    if (cmd == NULL)                                //malloc failed?
    {
        free_charchar_str(args);
        return (0);
    }
    
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

void print_error_create_cmdlist()
{
    ft_putstr_fd("cmd_list: ", STDERR_FILENO);
    ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
}

t_cmd *create_cmd(char *command, char **args, t_list *inout_list)
{
    t_cmd 	*cmd;

    cmd = malloc(sizeof(t_cmd));                                              //malloc failed?
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

    inout = malloc(sizeof(t_inout));                                            //malloc failed?
    if (inout == NULL)
        return (NULL);

    inout->type = type;
	inout->file = file;
	inout->heredoc = heredoc;
	inout->delimiter = delimiter;

    return (inout);
}

