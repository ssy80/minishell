/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_expanddollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:49:28 by yoong             #+#    #+#             */
/*   Updated: 2024/10/10 13:56:16 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

bool	schar(char s)
{
	if (s == '"' || s == '\'' || s == ' ' \
	|| s == '$' || s == '/' || s == ':' || (ft_isalnum(s) == 0))
		return (true);
	return (false);
}


void	fillstack(t_stack *stack, t_data *data, char *buf)
{
	char	*env;
	int		i;

	i = -1;
	env = getenvvar(buf, data);
	while (env[++i])
		stack->line[stack->tail++] = env[i];
}

void	expandss(t_stack *stack, char *s, t_data *data)
{
	int		i;
	int		j;
	char	buf[MAXLEN];

	i = -1;
	ft_bzero(stack, sizeof(t_stack));
	ft_bzero(buf, sizeof(char) * MAXLEN);
	while (s[++i])
	{
		j = 0;
		if (s[i] == '$')
		{
			while (++j >= 0 && s[i + j] && !schar(s[i + j]) && j < MAXLEN - 1)
				buf[j - 1] = s[i + j];
			i += j - 1;
			fillstack(stack, data, buf);
			continue ;
		}
		stack->line[stack->tail++] = s[i];
	}
}
