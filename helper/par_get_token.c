/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_get_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:36:43 by yoong             #+#    #+#             */
/*   Updated: 2024/08/03 17:36:47 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse1q(t_data *data, int i, int start)
{
	if (!data->buf[i])
		return (setdatatkn(data, i, start), i);
	if (data->buf[i] == '\'' && !is_sym(data->buf[i + 1]) && \
	!is_whitesp(data->buf[i + 1]))
		return (parsechar(data, i + 1, start));
	if (data->buf[i] == '\'')
		return (setdatatkn(data, i + 1, start), i + 1);
	return (parse1q(data, i + 1, start));
}

int	parse2q(t_data *data, int i, int start)
{
	if (!data->buf[i])
		return (setdatatkn(data, i, start), i);
	if (data->buf[i] == '"' && !is_sym(data->buf[i + 1]) && \
	!is_whitesp(data->buf[i + 1]))
		return (parsechar(data, i + 1, start));
	if (data->buf[i] == '"')
		return (setdatatkn(data, i + 1, start), i + 1);
	return (parse2q(data, i + 1, start));
}

int	parsechar(t_data *data, int i, int start)
{
	if (!data->buf[i] || is_sym(data->buf[i]) || is_whitesp(data->buf[i]))
		return (setdatatkn(data, i, start), i);
	if (data->buf[i] == '\'')
		return (parse1q(data, i + 1, start));
	if (data->buf[i] == '"')
		return (parse2q(data, i + 1, start));
	return (parsechar(data, i + 1, start));
}

int	parsesym(t_data *data, int i, int start)
{
	if (!is_sym(data->buf[i]))
		return (setdatatkn(data, i, start), i);
	if (data->buf[i] == '<' && data->buf[i + 1] == '<')
		return (setdatatkn(data, i + 2, start), i + 2);
	if (data->buf[i] == '>' && data->buf[i + 1] == '>')
		return (setdatatkn(data, i + 2, start), i + 2);
	if (data->buf[i] == '|')
		return (setdatatkn(data, i + 1, start), i + 1);
	if (data->buf[i] == '<')
		return (setdatatkn(data, i + 1, start), i + 1);
	if (data->buf[i] == '>')
		return (setdatatkn(data, i + 1, start), i + 1);
	return (parsesym(data, i + 1, start));
}
