/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:52:18 by yoong             #+#    #+#             */
/*   Updated: 2024/09/18 14:52:33 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// a[0] index for s
// a[1] index for line
void	exp1q(char *s, int a[2], char *line, t_data *data)
{
	while (s[a[0]] && s[a[0]] != '\'')
	{
		line[a[1]++] = s[a[0]++];
		if (a[1] >= MAXLEN)
			return (freedatacmd(data), freenullall(data), exitcl(1)); 
	}
	a[0]++;
}

// special character are being treated as normal character. will differ from bash behaviour
void	exp_s(char *s, int a[2], char *line, t_data *data)
{
	char	buf[MAXLEN];
	int		i;

	i = 0;
	// a[0]++;
	if (s[a[0]] >= '0' && s[a[0]] <= '9')
		return (a[0]++, (void) 0);
	while (s[a[0]])
	{
		if (s[a[0]] == '"' || s[a[0]] == '\'' || s[a[0]] == ' ' || s[a[0]] == '$')
		{
			a[0]++;
			break ;
		}
		buf[i++] = s[a[0]++];
	}
	buf[i] = '\0';
	if (i == 0)
		return ;
	i = -1;
	s = getenvvar(buf, data);
	while (s[++i] && a[1] < MAXLEN)
		line[a[1]++] = s[i];
}

void	exp2q(char *s, int a[2], char *line, t_data *data)
{
	while (s[a[0]] && s[a[0]] !='"')
	{
		if (s[a[0]] == '$')
			return exp_s(s, a, line, data), exp2q(s, a, line, data);
		line[a[1]] = s[a[0]];
		a[1]++;
		a[0]++;
	}
}

void	exptkn(char *s, int a[2], char *line, t_data *data)
{
	while (s[a[0]])
	{
		if (s[a[0]] == '\'')
			return a[0]++, exp1q(s, a, line, data), exptkn(s, a, line, data);
		if (s[a[0]] == '"')
			return a[0]++, exp2q(s, a, line, data), exptkn(s, a, line, data);
		if (s[a[0]] == '$')
			return a[0]++, exp_s(s, a, line, data), exptkn(s, a, line, data);
		line[a[1]] = s[a[0]];
		a[0]++;
		a[1]++;
	}
}

void	expander(char *s, t_data *data)
{
	int	a[2];
	char line[MAXEXP];

	ft_bzero(a, sizeof(int) * 2);
	ft_bzero(line, sizeof(char) * MAXEXP);
	exptkn(s, a, line, data);
	printf("%s\n", line);
}