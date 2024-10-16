/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:20:22 by ssian             #+#    #+#             */
/*   Updated: 2024/10/16 14:09:52 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	process_cmd(t_list *cmd_list, int size, t_data *data)
{
	if (size == 1)
		do_single_cmd(data);
	else if (size > 1)
		do_multiple_command(cmd_list, size, data);
}

static void	free_pidt_pipe(pid_t *pidt, int **pipefd, int size)
{
	free_pidt(pidt);
	free_pipefd_all(pipefd, size);
}

int	process_cmd_list(t_list *cmd_list, t_data *data)
{
	int		size;
	int		heredoc_status;

	data->pipefd = NULL;
	data->pidt = NULL;
	heredoc_status = do_heredoc(cmd_list, data);
	if (heredoc_status <= 0)
		return (heredoc_status);
	size = 0;
	size = ft_lstsize(cmd_list);
	if (size > 0)
	{
		data->pipefd = get_pipe(size - 1);
		if (data->pipefd == NULL)
			return (0);
		data->pidt = get_pidt(size);
		if (data->pidt == NULL)
			return (0);
	}
	process_cmd(cmd_list, size, data);
	return (free_pidt_pipe(data->pidt, data->pipefd, size - 1), 1);
}
