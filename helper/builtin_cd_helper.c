/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:15:39 by ssian             #+#    #+#             */
/*   Updated: 2024/09/28 23:15:42 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void error_no_home()
{
    ft_putstr_fd("cd: ", STDERR_FILENO);
    ft_putstr_fd("HOME not set\n", STDERR_FILENO);
}

void error_cd(t_data *data)
{
    ft_putstr_fd("cd: ", STDERR_FILENO);
    ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
    free_all(data);
    exit(EXIT_FAILURE);
}

char *get_pwd()
{
    char *path;

    path = malloc(sizeof(char) * MAXLEN);
    if (path == NULL)
        return (NULL);
    else
    {
        getcwd(path, sizeof(char) * MAXLEN);
        return (path);
    }
}