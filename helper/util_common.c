/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:59:27 by ssian             #+#    #+#             */
/*   Updated: 2024/09/28 10:59:29 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int equals(char *s1, char *s2)
{
    int i;

    if (s1 == NULL || s2 == NULL)
        return (0);
    i = 0;
    while(s1[i] || s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    return (1);
}

int is_dir(char *command) 
{
    struct stat sbuf;

    if (stat(command, &sbuf) != 0) 
        return (0);
    return S_ISDIR(sbuf.st_mode);
}

int	get_args_len(char **args)
{
	int i;

	if (args == NULL)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}