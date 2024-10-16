/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_get_token2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:58:40 by yoong             #+#    #+#             */
/*   Updated: 2024/10/02 12:58:41 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	parsenum(t_data *data, int i, int start)
{
	if (data->buf[i] < '0' || data->buf[i] > '9')
		return (i);
	return (parsenum(data, i + 1, start));
}

void	setdatatkn(t_data *data, int i, int start)
{
	data->tkn[data->itr][0] = start;
	data->tkn[data->itr][1] = i;
	data->itr++;
}

// handle str and return back start and end index of each token
// serparator is |, > and <, result stored in data.tkn
void	gettkn(t_data *data, int i, int start)
{
	int	k;

	if (!data->buf[i])
		return ;
	i = parsespace(data, i, start);
	if (data->buf[i] && data->buf[i] == '\'')
		return (k = parse1q(data, i + 1, i), gettkn(data, k, k));
	if (data->buf[i] && data->buf[i] == '"')
		return (k = parse2q(data, i + 1, i), gettkn(data, k, k));
	if (data->buf[i] && !is_sym(data->buf[i]))
		return (k = parsechar(data, i, i), gettkn(data, k, k));
	if (data->buf[i] && is_sym(data->buf[i]))
		return (k = parsesym(data, i, i), gettkn(data, k, k));
	return (gettkn(data, i + 1, i));
}

void	loadcmdtkn(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->itr)
	{
		data->cmd[i] = ft_calloc(data->tkn[i][1] - data->tkn[i][0] + 1, \
		sizeof(char));
		if (!data->cmd[i])
			return (freedatacmd(data), freenullall(data), exitcl(1));
		j = data->tkn[i][0];
		while (j < data->tkn[i][1])
		{
			data->cmd[i][j - data->tkn[i][0]] = data->buf[j];
			j++;
		}
	}
}
