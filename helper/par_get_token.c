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

// check for white space char  \t\r\n\v
_Bool	is_whitesp(char s)
{
	char	a[128];

	ft_bzero(a, sizeof(char) * 128);
	a[' '] = '1';
	a['\t'] = '1';
	a['\r'] = '1';
	a['\n'] = '1';
	a['\v'] = '1';
	if (a[(int)s] == '1')
		return (true);
	return (false);
}

// all special char in bash:
// ~`#$&*()\|[]{};'"<>/?!=+-
// need to handle special char below
// <>|$"'&&||<<>>=
// check for symbol	<|>&;()
_Bool	is_sym(char s)
{
	char	a[128];

	ft_bzero(a, sizeof(char) * 128);
	a['<'] = '1';
	a['|'] = '1';
	a['>'] = '1';
	a['='] = '1';
	if (a[(int)s] == '1')
		return (true);
	return (false);
}

int parse1q(t_data *data, int i, int start)
{
	if (data->buf[i] == '\'')
		return i;
	return parse1q(data, i + 1, start);
}

int parse2q(t_data *data, int i, int start)
{
	if (data->buf[i] == '"')
		return i;
	return parse1q(data, i + 1, start);
}

int parsesym(t_data *data, int i, int start)
{
	if (!is_sym(data->buf[i]))
	{
		data->tkn[data->itr][0] = start;
		data->tkn[data->itr][1] = i;
		data->itr++;
		return i;
	}
	return parsesym(data, i+1, start);
}

int parsechar(t_data *data, int i, int start)
{
	if (!data->buf[i] || is_sym(data->buf[i]) || data->buf[i] == ' ')
	{
		data->tkn[data->itr][0] = start;
		data->tkn[data->itr][1] = i;
		data->itr++;
		return i;
	}
	return parsechar(data, i+1, start);
}

int	parsenum(t_data *data, int i, int start)
{
	if (data->buf[i] < '0' || data->buf[i] > '9')
		return i;
	return parsenum(data, i + 1, start);
}

int parsespace(t_data *data, int i, int start)
{
	if (!is_whitesp(data->buf[i]))
		return i;
	return parsespace(data, i + 1, start);
}

void	parsecmd(t_data *data, int i, int start)
{
	if (!data->buf[i])
		return ;
	
	i = parsespace(data, i, start);
	if (data->buf[i] && !is_sym(data->buf[i]))
		i = parsechar(data, i, i);
	i = parsespace(data, i, start);
	if (data->buf[i] && is_sym(data->buf[i]))
		i = parsesym(data, i, i);
	return parsecmd(data, i, i);
}