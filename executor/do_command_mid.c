/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command_mid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:18:11 by ssian             #+#    #+#             */
/*   Updated: 2024/10/16 14:11:57 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	close_pipes(int pipe1, int pipe2)
{
	close(pipe1);
	close(pipe2);
}

void	do_command_mid(t_cmd *cmd, int i, t_data *data)
{
	int	exit_status;

	exit_status = 0;
	if (data->pidt[i] == 0)
	{
		close(data->pipefd[i - 1][1]);
		close(data->pipefd[i][0]);
		dup2(data->pipefd[i - 1][0], STDIN_FILENO);
		close(data->pipefd[i - 1][0]);
		dup2(data->pipefd[i][1], STDOUT_FILENO);
		close(data->pipefd[i][1]);
		if (cmd->inout_list != NULL)
			do_inout(cmd->inout_list, data);
		if (cmd->cmd != NULL)
		{
			if (is_builtin_fn(cmd->cmd) == 1)
				exit_status = do_builtin(cmd, data);
			else
				do_command(cmd, data);
		}
		free_all(data);
		exit(exit_status);
	}
	else
		close_pipes(data->pipefd[i - 1][0], data->pipefd[i - 1][1]);
}
