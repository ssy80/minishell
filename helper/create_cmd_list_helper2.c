/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list_helper2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:29:51 by ssian             #+#    #+#             */
/*   Updated: 2024/09/27 13:29:53 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	print_error_create_cmdlist()
{
    ft_putstr_fd("cmd_list: ", STDERR_FILENO);
    ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
}

char	**get_null_args()
{
	char	**new_args;

	new_args = malloc(sizeof(char *));
    if (new_args == NULL)
        return (NULL);
    else
    {
        new_args[0] = NULL;
        return (new_args);
    }
}

char	**add_arg(char **args, char *arg)
{
	int		i;
	int		size;
	char	**new_args;
	
	size = get_args_len(args);
	size = size + 1 + 1;
	new_args = malloc(sizeof(char *) * size);
    if (new_args == NULL)
    {                    
        return (free(args), NULL);
    }
	i = 0;
	while (i < (size - 2))
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = arg;
	i++;
	new_args[i] = NULL;
    free(args);
    args = NULL;
	return (new_args);
}

int is_inout(char *token)
{
	if (equals(token, "<"))
		return (2);
	else if (equals(token, "<<"))
		return (3);
	else if (equals(token, ">"))
		return (0);
	else if (equals(token, ">>"))
		return (1);
	else
		return (-1);
}