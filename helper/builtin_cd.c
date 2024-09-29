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

static int update_env_var(char *new_pwd, t_data *data)
{
    if (is_var_in_env(new_pwd, data) == 1)                        //replace tmp later
    {
        if (replace_var_in_env(new_pwd, data) == 0)               //error malloc??
            return (0);                        
    }
    else                                                         //add new env var to list
    {
        if (addenvvar(new_pwd, data) == -1)
            return (0);
    }
    return (1);
}

static int cd_home(t_data *data)
{
    char *new_pwd;
    char *new_path;

    if (is_var_in_env("HOME=", data) == 0)
        error_no_home();
    else
    {
        if (chdir(getenvvar("HOME", data)) == 0)
        {
            new_path = get_pwd();
            if (new_path == NULL)
                return (0);
            new_pwd = ft_strjoin("PWD=", new_path);
            free(new_path);
            if (new_pwd == NULL)
                error_cd(data);
            if (update_env_var(new_pwd, data) == 0)
                return (free(new_pwd), 0);
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
        new_path = get_pwd();
        if (new_path == NULL)
            return (0);
        new_pwd = ft_strjoin("PWD=", new_path);
        if (new_pwd == NULL)
            return (free(new_path), 0);
        free(new_path);
        if (update_env_var(new_pwd, data) == 0)
            return (free(new_pwd), 0);
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
    if (count == 0)
    {
        if (cd_home(data) == 0)
            error_cd(data);
    }
    else if (count == 1)
    {
        if (cd_dir(args, data) == 0)
            error_cd(data);
    }
    else if (count > 1)
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        ft_putstr_fd("too many arguments\n", STDERR_FILENO);
    }
}