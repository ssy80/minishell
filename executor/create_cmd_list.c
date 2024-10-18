/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:25:59 by ssian             #+#    #+#             */
/*   Updated: 2024/10/18 12:09:57 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	do_is_pipe(t_ccmd *ccmd)
{
	if (add_cmd(ccmd->command, ccmd->args, ccmd->inout_list,
			&(ccmd->cmd_list)) == 0)
		return (print_error_create_cmdlist(), 0);
	ccmd->command = NULL;
	ccmd->args = NULL;
	ccmd->inout_list = NULL;
	return (1);
}

static int	do_last(t_data *data, t_ccmd *ccmd, int *i)
{
	if (expand_str(*i, data) == 0)
		return (print_error_create_cmdlist(), 0);
	if (ccmd->command == NULL)
	{
		ccmd->command = data->cmd[*i];
		ccmd->args = add_arg(ccmd->args, data->cmd[*i]);
		if (ccmd->args == NULL)
			return (print_error_create_cmdlist(), 0);
	}
	else
	{
		ccmd->args = add_arg(ccmd->args, data->cmd[*i]);
		if (ccmd->args == NULL)
			return (print_error_create_cmdlist(), 0);
	}
	if (add_cmd(ccmd->command, ccmd->args,
			ccmd->inout_list, &(ccmd->cmd_list)) == 0)
		return (print_error_create_cmdlist(), 0);
	ccmd->command = NULL;
	ccmd->args = NULL;
	ccmd->inout_list = NULL;
	return (1);
}

static int	do_others(t_data *data, t_ccmd *ccmd, int *i)
{
	if (expand_str(*i, data) == 0)
		return (print_error_create_cmdlist(), 0);
	if (ccmd->command == NULL)
	{
		ccmd->command = data->cmd[*i];
		ccmd->args = add_arg(ccmd->args, data->cmd[*i]);
		if (ccmd->args == NULL)
			return (print_error_create_cmdlist(), 0);
	}
	else
	{
		ccmd->args = add_arg(ccmd->args, data->cmd[*i]);
		if (ccmd->args == NULL)
			return (print_error_create_cmdlist(), 0);
	}
	return (1);
}

static int	do_parsing(t_data *data, t_ccmd *ccmd, int *i)
{
	if (is_inout(data->cmd[*i]) > -1)
	{
		if (do_is_inout(data, ccmd, i) == 0)
			return (0);
	}
	else if (equals(data->cmd[*i], "|"))
	{
		if (do_is_pipe(ccmd) == 0)
			return (0);
	}
	else if (*i == (data->itr - 1))
	{
		if (do_last(data, ccmd, i) == 0)
			return (0);
	}
	else
	{
		if (do_others(data, ccmd, i) == 0)
			return (0);
	}
	return (1);
}

t_list	*create_cmd_list(t_data *data)
{
	int		i;
	t_ccmd	ccmd;

	ft_bzero(&ccmd, sizeof(t_ccmd));
	ccmd.command = NULL;
	ccmd.args = NULL;
	ccmd.cmd_list = NULL;
	ccmd.inout_list = NULL;
	i = 0;
	while (i < data->itr)
	{
		if (do_parsing(data, &ccmd, &i) == 0)
			return (free_inoutlist(ccmd.inout_list),
				free_cmdlist(ccmd.cmd_list), NULL);
		i++;
	}
	return (ccmd.cmd_list);
}
