/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:24:27 by ssian             #+#    #+#             */
/*   Updated: 2024/08/15 10:24:32 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

/*static int is_builtin_fn(char *cmd)
{
    if (equals(cmd, "echo") == 1)
        return (1);
    if (equals(cmd, "cd") == 1)
        return (1);
    if (equals(cmd, "pwd") == 1)
        return (1);
    if (equals(cmd, "export") == 1)
        return (1);
    if (equals(cmd, "unset") == 1)
        return (1);
    if (equals(cmd, "env") == 1)
        return (1);
    if (equals(cmd, "exit") == 1)
        return (1);
    return (0);
}*/

static char *do_pwd(void)
{
    //char	tmp[MAXLEN];
    char    *tmp;
    int     size;

    tmp = malloc(sizeof(char) * (MAXLEN + 1 + 1)); //1 for '\n', 1 for '\0'
    ft_bzero(tmp, (MAXLEN + 1 + 1));

	getcwd(tmp, sizeof(char) * MAXLEN);

    size = ft_strlen(tmp);
    tmp[size] = '\n';
    
    return (tmp);
}

static char *do_echo(char **args)
{
    char    *tmp;
    int     flag_n;
    int     size;
    int     i;
    int     k;
    int     j;

    tmp = NULL;
    flag_n = 0; //with \n
    if (args[0] == NULL)
        return ("\n");
    if (equals(args[0], "-n"))
        flag_n = 1;      //no \n
    i = flag_n;
    size = 0;
    while (args[i])
    {
        size = size + ft_strlen(args[i]) + 1;
        i++;
    }
    size--;
    if (flag_n == 0)
        size++;
    tmp = malloc(sizeof(char) * (size + 1) );
    ft_bzero(tmp, (size + 1));
    i = flag_n;
    j = 0;
    while (args[i])
    {
        k = 0;
        
        while(args[i][k])
        {
            tmp[j] = args[i][k];
            j++;
            k++;
        }
        i++;
        if (args[i] != NULL)
        {
            tmp[j] = ' ';
            j++;
        }
    }
    if (flag_n == 0)
        tmp[j] = '\n';
    
    return (tmp);
}



static char *execute_cmd(t_list *cmd_list, char **child_args)
{
    t_token *token;

    //(void)child_args;
    token = (t_token *)(cmd_list->content); //get cmd to execute
    
    //builtin cmd
    if (equals(token->cmd, "echo") == 1)
        return (do_echo(child_args));
    //if (equals(token->cmd, "cd") == 1)
    //    return (do_cd(child_args));
    if (equals(token->cmd, "pwd") == 1)
        return (do_pwd());
    //if (equals(token->cmd, "export") == 1)
    //    return (do_export(child_args));
    //if (equals(token->cmd, "unset") == 1)
    //    return (do_unset(child_args));
    //if (equals(token->cmd, "env") == 1)
    //    return (do_env(child_args));
    //if (equals(token->cmd, "exit") == 1)
    //    return (do_exit(child_args));

    //other cmd
    //fork a child process, execev the cmd with args , get output
    return (do_other(cmd_list, child_args));

    //return (NULL);
}

static int get_args_size(t_list *cmd_list)
{
    t_token *token;
    int i;

    if (cmd_list->next == NULL)
        return (0);
    cmd_list = cmd_list->next;
    token = (t_token *)(cmd_list->content);
    i = 0;
    while (token->type == 1)
    {
        i++;
        if(cmd_list->next == NULL)
            break;
        cmd_list = cmd_list->next;
        token = (t_token *)(cmd_list->content);
    }
    return (i);
}

static char **get_child_args(t_list *cmd_list)
{
    t_token *token;
    char    **args;
    int     size;
    int     i;

    size = get_args_size(cmd_list);
//printf("size: %d\n", size);
    args = malloc(sizeof(char *) * (size + 1));
    if (args == NULL)
        return (NULL);
    args[size] = NULL;
    if (cmd_list->next == NULL)
    {
        return (args);
    }

    cmd_list = cmd_list->next;
    token = (t_token *)(cmd_list->content);
    i = 0;
    while (token->type == 1)
    {
        args[i] = token->arg;
        i++;
        if(cmd_list->next == NULL)
            break;
        cmd_list = cmd_list->next;
        token = (t_token *)(cmd_list->content);
    }
    return (args);
}

static t_list *process_cmd(t_list *cmd_list)
{
    t_token *token;
    char    *output;
    char    **child_args;

    output = NULL;

    while (cmd_list != NULL)
    {
        token = (t_token *)(cmd_list->content);

        if (token->type == 0)//cmd
        {
            
            //check if builtin cmd
            //if (is_builtin_fn(token->cmd) == 1)
            //{
                
                printf("cmd: %s\n", token->cmd);
                child_args = get_child_args(cmd_list);
                /*if (child_args == NULL)
                    printf("--1--\n");
                int i = 0;
                while (child_args[i])
                {
                    printf("args: %s\n", child_args[i]);
                    i++;
                }*/
               output = execute_cmd(cmd_list, child_args);
               if (output)
                    ft_putstr_fd(output, STDOUT_FILENO);
	            //ft_putstr_fd("\n", STDOUT_FILENO);
            //}
            

        }
        else if (token->type == 2)//operator
        {

        }
        cmd_list = cmd_list->next;
    }
    return (NULL);

}

/*execute the pipeline of commands*/
void    execute_list(t_list *token_list)
{
    t_token *token;
    t_list  *cmd_list;


    //while (token_list != NULL)
    // {
        token = (t_token *)(token_list->content);
        if (token->type == 0)//cmd
        {
            cmd_list = token_list;
            process_cmd(cmd_list);
        }
        else if (token->type == 2)//operator
        {
            cmd_list = token_list;
            //process_operator(cmd_list);
        }
        /*else if(token->type == 1)//arg - skip
        {
            ;
        }*/
        //token_list = token_list->next;
    //}
}

