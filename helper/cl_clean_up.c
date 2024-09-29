/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_clean_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:17:55 by yoong             #+#    #+#             */
/*   Updated: 2024/08/04 08:18:01 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// used when adding malloc pointer
void	setfreept(t_data *data, void *pt)
{
	if (data->ptno >= PTMAX)
		return (freenullall(data), ft_putstr_fd(M_MAX, 1), exit(1));
	data->freept[data->ptno] = pt;
	data->ptno++;
}

// used when exiting to free all pointer in data.freept
void	freenullall(t_data *data)
{
	while (--data->ptno >= 0)
	{
		free(data->freept[data->ptno]);
		data->freept[data->ptno] = NULL;
	}
	ft_lstclear(&(data->env), free);
	freenull(data->envc);
}

// free and null pointer so that double free pt will not cause error
// free null does nothing
void	freenull(void *pt)
{
	free(pt);
	pt = NULL;
}

// close fd 0, 1 ,2 before exiting
void	exitcl(int code)
{
	close(0);
	close(1);
	close(2);
	rl_clear_history();
	exit(code);
}

void	freedatacmd(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->itr)
	{
		free(data->cmd[i]);
		data->cmd[i] = NULL;
	}
}
