/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:15:09 by ssian             #+#    #+#             */
/*   Updated: 2024/10/14 12:51:43 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	error_fork(t_data *data)
{
	perror("fork failed!");
	free_all(data);
	exit(EXIT_FAILURE);
}

void	do_command_last(t_cmd *cmd, int pipefd_in[], pid_t pidt, t_data *data)          
{
	int	exit_status;

	exit_status = 0;
	if (pidt == 0) 
	{
		close(pipefd_in[1]);
		dup2(pipefd_in[0], STDIN_FILENO);
		close(pipefd_in[0]);
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
	{
		close(pipefd_in[0]);
		close(pipefd_in[1]);
	}
}
