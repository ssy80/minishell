/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:12:28 by ssian             #+#    #+#             */
/*   Updated: 2024/09/22 16:12:30 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void print_not_valid_error(char *str)
{
    ft_putstr_fd("export: ", STDERR_FILENO);
    ft_putstr_fd("'", STDERR_FILENO);
    ft_putstr_fd(str, STDERR_FILENO);
    ft_putstr_fd("'", STDERR_FILENO);
    ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
}

static void error_export(t_data *data)
{
    ft_putstr_fd("export: ", STDERR_FILENO);
    ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
    free_all(data);
    exit(EXIT_FAILURE);
}

static int is_contain(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}

/* only valid if start with _ or alphabets */
static int is_valid_var_name(char *str)
{
    int i;

    i = 0;
    if (str[i] != '_' && ft_isalpha(str[i]) == 0)
        return (0);
    i++;
    while (str[i])
    {
        if (str[i] == '=')
            break;
        if (str[i] != '_' && (ft_isalnum(str[i]) == 0))
            return (0);
        i++;
    }
    return (1);
}

/* ignored arg without '=', [0] first char '=' is invalid format */
static int check_error_args(char *str)
{
    if (is_valid_var_name(str) == 0)
    {
        print_not_valid_error(str);
        return (0);
    }
    if (str[0] == '=')
    {
        print_not_valid_error(str);
        return (0);
    }
    return (1);
}

static void do_export(char *str, t_data *data)
{
    if (is_var_in_env(str, data) == 1)                        
        {
            if (replace_var_in_env(str, data) == 0)
                error_export(data);                      
        }
        else
        {
            if (addenvvar(str, data) == -1)
                error_export(data);
        }
}
/*if starts with a= already in list, replace with new a=... 
  if not in list then add args[i] to it.
  if invalid format "export a"? - will be ignored no error msg. 
  if invalid format "=" or "=aaa"? will have error msg.
  success = 1, failed = 0
*/
int builtin_export(char **args, t_data *data)
{
    int i;
    int status;

    status = 1;
    i = 1;
    while (args[i])
    {
        if (check_error_args(args[i]) == 0)
        {
            status = 0;
            i++;
            continue;
        }
        if (is_contain(args[i], '=') == 0)
        {
            i++;
            continue;
        }
        do_export(args[i], data);
        /*if (is_var_in_env(args[i], data) == 1)                        
        {
            if (replace_var_in_env(args[i], data) == 0)
                error_export(data);                      
        }
        else
        {
            if (addenvvar(args[i], data) == -1)
                error_export(data);
        }*/
        i++;
    }
    return (status);
}