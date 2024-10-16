/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_multiple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:04:08 by ssian             #+#    #+#             */
/*   Updated: 2024/10/16 14:21:48 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	error_pipe(t_data *data)
{
	perror("pipe create failed!");
	free_all(data);
	exit(EXIT_FAILURE);
}

static void	wait_process_end(pid_t *pidt, int size, t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	status = 0;
	pid = 0;
	while (i < size)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == pidt[size -1])
		{
			if (WIFSIGNALED(status))
				update_exit_status(128 + WTERMSIG(status), data);
			else if (WIFEXITED(status))
				update_exit_status(WEXITSTATUS(status), data);
		}
		i++;
	}
}

void	do_multiple_command(t_list *cmd_list, int size, t_data *data)
{
	int		i;

	i = 0;
	while (cmd_list != NULL)
	{
		if (i != (size - 1))
		{
			if (pipe(data->pipefd[i]) == -1)
				error_pipe(data);
		}
		data->pidt[i] = fork();
		if (data->pidt[i] == -1)
			error_fork(data);
		if (i == 0)
			do_command_first((t_cmd *)(cmd_list->content),
				data->pipefd[i], data->pidt[i], data);
		else if (i == (size - 1))
			do_command_last((t_cmd *)(cmd_list->content),
				data->pipefd[i - 1], data->pidt[i], data);
		else
			do_command_mid((t_cmd *)(cmd_list->content), i, data);
		cmd_list = cmd_list->next;
		i++;
	}
	wait_process_end(data->pidt, size, data);
}
