/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_expand5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:13:13 by yoong             #+#    #+#             */
/*   Updated: 2024/10/13 16:13:15 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	copylinetobuf(char *line, t_data *data)
{
	int	i;

	i = -1;
	ft_bzero(data->buf, sizeof(char) * MAXLEN);
	while (line[++i])
		data->buf[i] = line[i];
}

void	jointkn(t_data *data)
{
	char	line[5000];
	int		i;
	int		j;
	int		k;

	i = -1;
	k = -1;
	ft_bzero(line, sizeof(line));
	while (data->cmd[++i])
	{
		j = -1;
		while (data->cmd[i][++j])
			line[++k] = data->cmd[i][j];
		if (i < data->itr - 1)
			line[++k] = ' ';
	}
	copylinetobuf(line, data);
}

void	retokenise(t_data *data)
{
	t_stack	stack;
	int		i;

	i = -1;
	jointkn(data);
	free_datacmd(data);
	data->itr = 0;
	ft_bzero(data->tkn, sizeof(data->tkn));
	gettkn(data, 0, 0);
	loadcmdtkn(data);
	while (data->cmd[++i])
	{
		if (ignoreexp(data->cmd[i]) || ignoreexp2(data->cmd[i]) || \
		(i > 0 && ft_strncmp(data->cmd[i - 1], "<<", 2) == 0))
			continue ;
		qremoval(data->cmd[i], &stack);
		free(data->cmd[i]);
		data->cmd[i] = ft_strdup(stack.line);
	}
}
