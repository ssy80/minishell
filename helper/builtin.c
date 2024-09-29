/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:35:52 by ssian             #+#    #+#             */
/*   Updated: 2024/09/18 13:35:55 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int is_builtin_fn(char *cmd)
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
}