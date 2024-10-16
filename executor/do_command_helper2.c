/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command_helper2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:18:58 by ssian             #+#    #+#             */
/*   Updated: 2024/10/16 11:26:58 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	error_execve(t_cmd *cmd, t_data *data)
{
	perror(cmd->cmd);
	free_all(data);
	if (errno == 2)
		exit(127);
	else
		exit(EXIT_FAILURE);
}

int	is_cmd_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	check_x_permission(char *command)
{
	if (access(command, X_OK) == -1)
		return (0);
	return (1);
}

int	check_got_file(char *command)
{
	if (access(command, F_OK) == -1)
		return (0);
	return (1);
}

char	*get_env_path(t_data *data)
{
	char	*path;

	path = getenvvar("PATH", data);
	return (path);
}
