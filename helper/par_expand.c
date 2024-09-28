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

void	exp_1s(char *s, int a[2], char *line)
{
	if (s[a[0]] == '\0' || s[a[0]] == ' ' || (a[0] > 0 && \
	s[a[0]] == '"' && (s[a[0] - 2] == '"' || s[a[0] - 2] == ' ') ))
	{
		line[a[1]] = '$';
		a[1]++;
	}
}

void 	exp_sq(int a[2], char *line, t_data *data)
{
	int i;
	char *exit;

	i = 0;
	exit = getenvvar("EXIT_STATUS", data);
	while (exit[i])
		i++;
	if (i == 0)
		exit = "0";
	i = -1;
	while (exit[++i])
		line[a[1]++] = exit[i];
}

// special character are being treated as normal character. will differ from bash behaviour
void	exp_s(char *s, int a[2], char *line, t_data *data)
{
	char	buf[MAXLEN];
	int		i;

	i = 0;
	if (s[a[0]] >= '0' && s[a[0]] <= '9')
		return (a[0]++, (void) 0);
	if (s[a[0]] == '?')
		return (a[0]++, exp_sq(a, line, data));
	while (s[a[0]])
	{
		if (s[a[0]] == '"' || s[a[0]] == '\'' || s[a[0]] == ' ' || s[a[0]] == '$')
			break ;
		buf[i++] = s[a[0]++];
	}
	buf[i] = '\0';
	if (i == 0)
		return exp_1s(s, a, line);
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
			return a[0]++, exp_s(s, a, line, data), exp2q(s, a, line, data);
		line[a[1]] = s[a[0]];
		a[1]++;
		a[0]++;
	}
	if (s[a[0]] && s[a[0]] =='"')
		a[0]++;
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

int	expander(char *s, t_data *data, int i)
{
	int	a[2];
	char line[MAXEXP];
	char *str;

	ft_bzero(a, sizeof(int) * 2);
	ft_bzero(line, sizeof(char) * MAXEXP);
	exptkn(s, a, line, data);
	//printf("%s\n", line);

	str = ft_strdup(line);
	if (str == NULL)
		return (0);
	free(data->cmd[i]);
	data->cmd[i] = str;
	//printf("s: %s\n", data->cmd[i]);
	return (1);

}