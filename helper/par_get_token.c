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
	a['&'] = '1';
	a[';'] = '1';
	a['('] = '1';
	a[')'] = '1';
	if (a[(int)s] == '1')
		return (true);
	return (false);
}

// int	get_token(char **ps, char *es, char **q, char **eq)
// {
// 	char	*s;
// 	int		i;
// 	int		ret;

// 	i = 0;
// 	s = *ps;
// 	while (s[i] && is_whitesp(s[i]))
// 		i++;
// 	if (q)
// 		*q = &s[i];
// 	ret = s[i];
// 	return (ret);
// }