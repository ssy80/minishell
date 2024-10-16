/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list_helper3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 19:39:18 by ssian             #+#    #+#             */
/*   Updated: 2024/10/14 12:37:22 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_inout_list(t_list *inout_list)
{
	t_inout	*inout;

	while (inout_list != NULL)
	{
		inout = (t_inout *)(inout_list->content);
		printf("inout->type: %d\n", inout->type);
		printf("inout->file: %s\n", inout->file);
		printf("inout->heredoc: %s\n", inout->heredoc);
		printf("inout->delimiter: %s\n", inout->delimiter);
		inout_list = inout_list->next;
	}
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("args[%d]: %s\n", i, args[i]);
		i++;
	}
}

void	print_cmd(t_list *cmd_list)
{
	t_cmd	*cmd;

	while (cmd_list != NULL)
	{
		cmd = (t_cmd *)(cmd_list->content);
		printf("cmd->cmd: %s\n", cmd->cmd);
		print_args(cmd->args);
		print_inout_list(cmd->inout_list);
		cmd_list = cmd_list->next;
	}
}
