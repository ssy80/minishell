/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:22:20 by ssian             #+#    #+#             */
/*   Updated: 2024/09/09 20:22:25 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int is_inout(char *token)
{
	if (equals(token, "<"))
		return (2);                  //2 for infile
	else if (equals(token, "<<"))
		return (3);                  //3 for heredoc 
	else if (equals(token, ">"))
		return (0);                  //0 for create 
	else if (equals(token, ">>"))
		return (1);                  //1 for append 
	else
		return (-1);                 //not inout
}

int	get_args_len(char **args)
{
	int i;

	if (args == NULL)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}

char **add_arg(char **args, char *arg)
{
	int i;
	int size;
	char **new_args;
	
	size = get_args_len(args);
	size = size + 1 + 1;                         //1 for NULL, 1 for new arg

	new_args = malloc(sizeof(char *) * size);    //malloc failed?
    if (new_args == NULL)                       
    {
        return (free(args), NULL);
    }

	i = 0;
	while (i < (size - 2))
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = arg;
	i++;
	new_args[i] = NULL;                       //set last to NULL

    free(args);
    args = NULL;

	return (new_args);
}

char **get_null_args()
{
	char **new_args;

	new_args = malloc(sizeof(char *));       //malloc failed?
    if (new_args == NULL)
        return (NULL);
    else
    {
        new_args[0] = NULL;
        return (new_args);
    }
}


static int add_inout(t_list **inout_list, int inout_type, char *inout_value)
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

static int add_cmd(char *command, char **args, t_list *inout_list, t_list **cmd_list)
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

t_list *create_cmd_list(t_data *data)
{
	t_list  *cmd_list;
	t_list *inout_list;
	char	*command;
	char	**args;
	int inout_type;
    int i;

	command = NULL;
	args = NULL;
	cmd_list = NULL;
	inout_list = NULL;

	i = 0;

	while (i < data->itr)
	{
		inout_type = is_inout(data->cmd[i]);
		if (inout_type > -1)                                                //is inout(> >> << <) //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
        {
			i++;

            if (add_inout(&inout_list, inout_type, data->cmd[i]) == 0)       //error create inout
            {
                return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
            }
            if (i == (data->itr - 1))                                        //last item 
            {
                if (add_cmd(command, args, inout_list, &cmd_list) == 0)
                    return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
            }

		}
		else if (equals(data->cmd[i], "|"))                                   // | pipe
		{
            if (add_cmd(command, args, inout_list, &cmd_list) == 0)
                return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
            command = NULL;
            args = NULL;
            inout_list = NULL;
		}
        else if (i == (data->itr - 1))                                         //last item 
        {

            if (command == NULL)                                               // always command first
            {
				command = data->cmd[i];

                args = add_arg(args, data->cmd[i]);
                if (args == NULL)                                               //malloc failed?
                {
                    return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
                }
            }
			else                                                                //rest is arguments
            {
				args = add_arg(args, data->cmd[i]);                            
                if (args == NULL)                                               //malloc failed?
                {
                    return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
                }
            }

            if (add_cmd(command, args, inout_list, &cmd_list) == 0)
                return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
            command = NULL;
            args = NULL;
            inout_list = NULL;
        }
		else                                                                    // is command or args
		{
			if (command == NULL)                                                // always command first
            {
				command = data->cmd[i];
                args = add_arg(args, data->cmd[i]);
                if (args == NULL)                                               //malloc failed?
                    return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
            }
			else                                                               //rest is arguments
            {
				args = add_arg(args, data->cmd[i]);
                if (args == NULL)                                               //malloc failed?
                    return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
            }
		}
		i++;
	}
	return (cmd_list);
}