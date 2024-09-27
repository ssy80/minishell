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

static int is_valid_var_name(char *str)       //only valid if start with _ or alphabets
{
    int i;

    i = 0;
    if (str[i] != '_' && ft_isalpha(str[i]) == 0)
        return (0);
    i++;
    while (str[i] != '=')
    {
        if (str[i] != '_' && str[i] != '=' && ft_isalnum(str[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

static int check_error_args(char *str)
{
    if (ft_strchr(str, '=') == NULL)                          //ignored arg without '='
        return (1);
    if (str[0] == '=')                                        //[0] first char '=' is invalid format 
    {
        print_not_valid_error(str);
        return (1);
    }
    if (is_valid_var_name(str) == 0)                     //only valid if start with _ or alphabets
    {
        print_not_valid_error(str);
        return (1);
    }
    return (0);
}

/*if starts with a= already in list, replace with new a=... 
  if not in list then add args[i] to it.
  if invalid format "export a"? - will be ignored no error msg. 
  if invalid format "=" or "=aaa"? will have error msg.
*/
void builtin_export(char **args, t_data *data)
{
    int i;

    i = 1;
    while (args[i])
    {
        if (check_error_args(args[i]) == 1)
        {
            i++;
            continue;
        }
        if (is_var_in_env(args[i], data) == 1)                        
        {
            if (replace_var_in_env(args[i], data) == 0)               //error malloc??
                error_export(data);                      
        }
        else                                                         //add new env var to list
        {
            if (addenvvar(args[i], data) == -1)
                error_export(data);
        }
        i++;
    }
}