/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_get_token3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:59:57 by yoong             #+#    #+#             */
/*   Updated: 2024/10/02 13:00:04 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// check for white space char  \t\r\n\v
bool	is_whitesp(char s)
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
	if (s == '<' || s == '|' || s == '>')
		return (true);
	return (false);
}

int	parsespace(t_data *data, int i, int start)
{
	if (!is_whitesp(data->buf[i]))
		return (i);
	return (parsespace(data, i + 1, start));
}
