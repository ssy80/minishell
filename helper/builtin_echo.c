/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:12:05 by ssian             #+#    #+#             */
/*   Updated: 2024/09/22 16:12:07 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void builtin_echo(char **args)
{
    int i;
    int flag_n;

    flag_n = 1;
    i = 1;
    if (equals(args[i], "-n") == 1)
    {
        flag_n = 0;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1] != NULL)
            ft_putstr_fd(" ", STDOUT_FILENO);
        i++;
    }
    if (flag_n == 1)
        ft_putstr_fd("\n", STDOUT_FILENO);
}