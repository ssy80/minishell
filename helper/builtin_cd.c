/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:11:38 by ssian             #+#    #+#             */
/*   Updated: 2024/09/22 16:11:42 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static char *get_pwd()
{
    char *path;

    path = malloc(sizeof(char) * MAXLEN);                 //malloc failed ??
    if (path == NULL)
        return (NULL);
    else
    {
        getcwd(path, sizeof(char) * MAXLEN);
        return (path);
    }
}

static int check_cd_args_len(char **args)
{
    int i;
    int count;

    i = 1;
    count = 0;
    while (args[i])
    {
        count++;
        i++;
    }
    return (count);
}

static void error_cd(t_data *data)
{
    ft_putstr_fd("cd: ", STDERR_FILENO);
    ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
    free_all(data);
    exit(EXIT_FAILURE);
}

static int cd_home(t_data *data)
{
    char *new_pwd;

    if (is_var_in_env("HOME=", data) == 0)
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        ft_putstr_fd("HOME not set\n", STDERR_FILENO);
    }
    else
    {
        if (chdir(getenvvar("HOME", data)) == 0)
        {
            new_pwd = ft_strjoin("PWD=", getenvvar("HOME", data));       //get "PWD=$HOME" //set pwd to HOME path
            if (new_pwd == NULL)
                error_cd(data);
            if (is_var_in_env(new_pwd, data) == 1)                        
            {
                if (replace_var_in_env(new_pwd, data) == 0)               //error malloc??
                    return (free(new_pwd), 0);                       
            }
            else                                                         //add new env var to list
            {
                if (addenvvar(new_pwd, data) == -1)
                    return (free(new_pwd), 0);
            }
            free(new_pwd);
        }
        else
            perror("cd");
    }
    return (1);
}

static int cd_dir(char **args, t_data *data)
{
    char *new_pwd;
    char *new_path;

    if (chdir(args[1]) == 0) 
    {
        new_path = get_pwd();                                         //need free
        if (new_path == NULL)
            return (0);
        new_pwd = ft_strjoin("PWD=", new_path);                       //need free
        if (new_pwd == NULL)
            return (free(new_path), 0);
        free(new_path);
        if (is_var_in_env(new_pwd, data) == 1)                        //replace tmp later
        {
            if (replace_var_in_env(new_pwd, data) == 0)               //error malloc??
                return (free(new_pwd), 0);                        
        }
        else                                                         //add new env var to list
        {
            if (addenvvar(new_pwd, data) == -1)
                return (free(new_pwd), 0);
        }
        free(new_pwd);
    }
    else
        perror("cd");
    return (1);
}

void builtin_cd(char **args, t_data *data)
{
    int count;

    count = check_cd_args_len(args);
    if (count == 0)                                                           //cd to HOME dir
    {
        
        if (cd_home(data) == 0)
            error_cd(data);
    }
    else if (count == 1)                                                 //cd to args[1]
    {
        if (cd_dir(args, data) == 0)
            error_cd(data);
    }
    else if (count > 1)                                                 //error too many arguments
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        ft_putstr_fd("too many arguments\n", STDERR_FILENO);
    }
}