/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:51:06 by ssian             #+#    #+#             */
/*   Updated: 2024/09/27 22:51:08 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int  is_cmd_path(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '/') 
            return (1);
        i++;
    }
    return(0);
}

/* ls: /usr/bin + / + ls */
static char *form_filepath(char *split_path, char *cmd)
{
    char *command;
    char    *copy_command;

    command = NULL;
    copy_command = NULL;
    command = ft_strjoin(split_path, "/");
    if (command == NULL)
        return (NULL);
    copy_command = ft_strdup(command);
    if (copy_command == NULL)
        return (free(command), NULL);
    free(command);
    command = ft_strjoin(copy_command, cmd);
    if (command == NULL)
        return (free(copy_command), NULL);
    free(copy_command);
    return (command);
}

static char *get_filepath(char *env_path, char *cmd)
{
    int     i;
    char    **split_path;
    char    *command;                                       

    command = NULL;
    split_path = ft_split(env_path, ':');                  
    i = 0;
    while (split_path[i])
    {
        free(command);
        command = form_filepath(split_path[i], cmd);
        if (command == NULL)
            return (free_charchar_str(split_path), NULL);
        if (access(command, F_OK) == 0)
            return (free_charchar_str(split_path), command);
        i++;
    }
    return (free_charchar_str(split_path), free(command), NULL);
}

static char *get_command_path(char *cmd, t_data *data)
{
    char *command;
    char *env_path;

    if (is_cmd_path(cmd) == 1)
    {
        command = ft_strdup(cmd);
        if (command == NULL)
            return (NULL);
        return (command);
    }
    env_path = get_env_path(data);
    command = get_filepath(env_path, cmd);
    return (command);
}

void    do_command(t_cmd *cmd, t_data *data)
{
    char *command;
    char    **envp;

    if (ft_strlen(cmd->cmd) == 0)
        error_empty_command(data);
    //{
        //ft_putstr_fd(cmd->cmd, STDERR_FILENO);
        //ft_putstr_fd(": ", STDERR_FILENO);
        //ft_putstr_fd("No such file!\n", STDERR_FILENO);
    //    free_all(data);
    //    exit(EXIT_SUCCESS);
    //}

    if (is_dir(cmd->cmd) == 1)
        error_command_is_dir(cmd, data);
    command = get_command_path(cmd->cmd, data);
    if (command == NULL)
        error_no_command(cmd, data);
    else
    {
        envp = get_current_env(data);
        if (envp == NULL)
            error_no_env(cmd, data);
        if (execve(command, cmd->args, envp) == -1) 
        {
           
            
            free(envp);
            free(command);
            error_execve(cmd, data);
            
            /*perror(cmd->cmd);
            free_all(data);
            if (errno == 2)
                exit(127);
            else
                exit(EXIT_FAILURE);*/
        }
    }
}