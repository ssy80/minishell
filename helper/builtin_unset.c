/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:12:38 by ssian             #+#    #+#             */
/*   Updated: 2024/09/22 16:12:40 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void error_unset(t_data *data)
{
    ft_putstr_fd("unset: ", STDERR_FILENO);
    ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
    free_all(data);
    exit(EXIT_FAILURE);
}

/*look for the arg AA=aaa - AA in the env list, remove it if have*/
void builtin_unset(char **args, t_data *data)
{
    char *tmp;
    int i;

    i = 1;                                                  //start from [1], [0] is command 
    while (args[i])
    {
        tmp = ft_strjoin(args[i], "=");                     // AA=
        if (is_var_in_env(tmp, data) == 1)                  // got AA=               
        {
            if (remove_var_in_env(tmp, data) == 0)
            {
                free(tmp);
                error_unset(data);
            }
                //return (free(tmp), 0);
        }
        free(tmp);
        i++;
    }
    //return (1);
}