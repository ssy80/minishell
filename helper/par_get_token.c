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
	if (s == ' ' || s == '\t' || s == '\r' || s == '\n' || s == '\v')
		return (true);
	return (false);
}

// all special char in bash:
// ~`#$&*()\|[]{};'"<>/?!=+-
// need to handle special char below
// <>|$"'&&||<<>>=
// check for symbol	<|>&;()
bool	is_sym(char s)
{
	if (s == '<' || s == '|' || s == '>' || s == '=')
		return (true);
	return (false);
}

void	setdatatkn(t_data *data, int i, int start)
{
		data->tkn[data->itr][0] = start;
		data->tkn[data->itr][1] = i;
		data->itr++;
}

int	parse1q(t_data *data, int i, int start)
{
	if (!data->buf[i])
		return (setdatatkn(data, i, start), i);
	if (data->buf[i] == '\'' && !is_sym(data->buf[i + 1]) && !is_whitesp(data->buf[i + 1]))
		return (parsechar(data, i + 1, start));
	if (data->buf[i] == '\'')
		return (setdatatkn(data, i + 1, start), i + 1);
	return (parse1q(data, i + 1, start));
}

int	parse2q(t_data *data, int i, int start)
{
	if (!data->buf[i])
		return (setdatatkn(data, i, start), i);
	if (data->buf[i] == '"' && !is_sym(data->buf[i + 1]) && !is_whitesp(data->buf[i + 1]))
		return (parsechar(data, i + 1, start));
	if (data->buf[i] == '"')
		return (setdatatkn(data, i + 1, start), i + 1);
	return (parse2q(data, i + 1, start));
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

int	parsenum(t_data *data, int i, int start)
{
	if (data->buf[i] < '0' || data->buf[i] > '9')
		return (i);
	return (parsenum(data, i + 1, start));
}

int	parsespace(t_data *data, int i, int start)
{
	if (!is_whitesp(data->buf[i]))
		return (i);
	return (parsespace(data, i + 1, start));
}

// handle str and return back start and end index of each token
// serparator is |, > and <, result stored in data.tkn
void	gettkn(t_data *data, int i, int start)
{
	if (!data->buf[i])
		return ;
	i = parsespace(data, i, start);
	if (data->buf[i] && data->buf[i] == '\'')
		return (gettkn(data, i = parse1q(data, i + 1, i), i));
	if (data->buf[i] && data->buf[i] == '"')
		return (gettkn(data, i = parse2q(data, i + 1, i), i));
	if (data->buf[i] && !is_sym(data->buf[i]))
		return (gettkn(data, i = parsechar(data, i, i), i));
	if (data->buf[i] && is_sym(data->buf[i]))
		return (gettkn(data, i = parsesym(data, i, i), i));
	return (gettkn(data, i + 1, i));
}

void	loadcmdtkn(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->itr)
	{
		data->cmd[i] = ft_calloc(data->tkn[i][1] - data->tkn[i][0] + 1, sizeof(char));
		if (!data->cmd[i])
			return (freedatacmd(data), freenullall(data), exitcl(1));
		j = data->tkn[i][0];
		while (j < data->tkn[i][1])
		{
			data->cmd[i][j-data->tkn[i][0]] = data->buf[j];
			j++;
		}
	}
}