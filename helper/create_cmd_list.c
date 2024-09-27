/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:25:59 by ssian             #+#    #+#             */
/*   Updated: 2024/09/27 10:26:02 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

/*static int add_inout(t_list **inout_list, int inout_type, char *inout_value)
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
}*/



static int do_is_inout(t_data *data, t_ccmd *ccmd, int *i)
{
    int inout_type;

    inout_type = is_inout(data->cmd[*i]);
    *i = *i + 1;

    if (add_inout(&(ccmd->inout_list), inout_type, data->cmd[*i]) == 0)                       //error create inout
    {
        
        return (print_error_create_cmdlist(), 0);
        //return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
    }
    if (*i == (data->itr - 1))                                                             //last item 
    {
        if (add_cmd(ccmd->command, ccmd->args, ccmd->inout_list, &(ccmd->cmd_list)) == 0)
            return (print_error_create_cmdlist(), 0);
            //return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
    }
    return (1);
}

static int do_is_pipe(t_ccmd *ccmd)
{
    if (add_cmd(ccmd->command, ccmd->args, ccmd->inout_list, &(ccmd->cmd_list)) == 0)
    {
        return (print_error_create_cmdlist(), 0);
    }
        //return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
    ccmd->command = NULL;
    ccmd->args = NULL;
    ccmd->inout_list = NULL;
    return (1);
}

static int do_last(t_data *data, t_ccmd *ccmd, int *i)
{
    if (ccmd->command == NULL)                                               // always command first
    {
        ccmd->command = data->cmd[*i];

        ccmd->args = add_arg(ccmd->args, data->cmd[*i]);
        if (ccmd->args == NULL)                                               //malloc failed?
        {
            return (print_error_create_cmdlist(), 0);
            //return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
        }
    }
    else                                                                //rest is arguments
    {
        ccmd->args = add_arg(ccmd->args, data->cmd[*i]);                            
        if (ccmd->args == NULL)                                               //malloc failed?
        {
            return (print_error_create_cmdlist(), 0);
            //return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
        }
    }

    if (add_cmd(ccmd->command, ccmd->args, ccmd->inout_list, &(ccmd->cmd_list)) == 0)
        return (print_error_create_cmdlist(), 0);
        //return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
    ccmd->command = NULL;
    ccmd->args = NULL;
    ccmd->inout_list = NULL;
    return (1);
}

static int do_others(t_data *data, t_ccmd *ccmd, int *i)
{
    if (ccmd->command == NULL)                                                // always command first
    {
        ccmd->command = data->cmd[*i];
        ccmd->args = add_arg(ccmd->args, data->cmd[*i]);
        if (ccmd->args == NULL)
            return (print_error_create_cmdlist(), 0);                                                             //malloc failed?
            //return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
    }
    else                                                               //rest is arguments
    {
        ccmd->args = add_arg(ccmd->args, data->cmd[*i]);
        if (ccmd->args == NULL)
            return (print_error_create_cmdlist(), 0);                                               //malloc failed?
            //return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
    }
    return (1);
}



/**
typedef struct s_ccmd
{
	t_list  *cmd_list;
	t_list *inout_list;
	char	*command;
    char	**args;
}   t_ccmd;
*/
t_list *create_cmd_list(t_data *data)
{
	//t_list  *cmd_list;
	//t_list *inout_list;
	//char	*command;
	//char	**args;
	//int inout_type;
    int i;

	//command = NULL;
	//args = NULL;
	//cmd_list = NULL;
	//inout_list = NULL;

    t_ccmd ccmd;
    ft_bzero(&ccmd, sizeof(t_ccmd));
    //ccmd.command = NULL;
    //ccmd.args = NULL;
    //ccmd.cmd_list = NULL;
    //ccmd.inout_list = NULL;


	i = 0;

	while (i < data->itr)
	{
		//inout_type = is_inout(data->cmd[i]);
		//if (inout_type > -1)                                                //is inout(> >> << <) //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
        if (is_inout(data->cmd[i]) > -1)
        {
			//i++;

            if (do_is_inout(data, &ccmd, &i) == 0)                 //malloc failed ?
                return (free_inoutlist(ccmd.inout_list), free_cmdlist(ccmd.cmd_list), NULL);

            /*if (add_inout(&inout_list, inout_type, data->cmd[i]) == 0)       //error create inout
            {
                return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
            }
            if (i == (data->itr - 1))                                        //last item 
            {
                if (add_cmd(command, args, inout_list, &cmd_list) == 0)
                    return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
            }*/

		}
		else if (equals(data->cmd[i], "|"))                                   // | pipe
		{
            if (do_is_pipe(&ccmd) == 0)
                return (free_inoutlist(ccmd.inout_list), free_cmdlist(ccmd.cmd_list), NULL);

            /*if (add_cmd(command, args, inout_list, &cmd_list) == 0)
                return (free_inoutlist(inout_list), free_cmdlist(cmd_list), NULL);
            command = NULL;
            args = NULL;
            inout_list = NULL;*/
		}
        else if (i == (data->itr - 1))                                         //last item 
        {
            if (do_last(data, &ccmd, &i) == 0)
                return (free_inoutlist(ccmd.inout_list), free_cmdlist(ccmd.cmd_list), NULL);

            /*if (command == NULL)                                               // always command first
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
            inout_list = NULL;*/
        }
		else                                                                    // is command or args
		{
            if (do_others(data, &ccmd, &i) == 0)
                return (free_inoutlist(ccmd.inout_list), free_cmdlist(ccmd.cmd_list), NULL);


			/*if (command == NULL)                                                // always command first
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
            }*/
		}
		i++;
	}
	return (ccmd.cmd_list);
}

/*t_list *create_cmd_list(t_data *data)
{
	t_list  *cmd_list;
	t_list *inout_list;
	char	*command;
	char	**args;
	//int inout_type;
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
        //if (is_inout(data->cmd[i]) > -1)
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
}*/
