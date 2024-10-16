/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_expand3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:09:26 by yoong             #+#    #+#             */
/*   Updated: 2024/10/05 16:09:30 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// clone tkn from data.cmd for word splitting after $ expansion
// clear all data.cmd and data.itr = 0
void	clonetkn(char (*copy)[MAXLEN], t_data *data)
{
	int	i;
	int	j;

	ft_bzero(copy, sizeof(char) * MAXLEN * MAXLEN);
	i = -1;
	while (data->cmd[++i])
	{
		j = -1;
		while (data->cmd[i][++j])
			copy[i][j] = data->cmd[i][j];
	}
	free_datacmd(data);
	data->itr = 0;
}

// quote should be " or '
bool	skipquote(char *s, int *i, char quote, t_data *data)
{
	char	line[MAXLEN];
	int		j;

	j = 0;
	ft_bzero(&line, sizeof(char) * MAXLEN);
	if (s[*i] == quote)
	{
		line[j] = quote;
		while (s[++(*i)] && s[*i] != ' ')
			line[++j] = s[*i];
	}
	data->cmd[data->itr++] = ft_strdup(line);
	return (true);
}

const char	*tranform(char *line)
{
	int	i;

	if (ft_strncmp("|", line, 2) == 0)
		return ("|");
	if (ft_strncmp("<", line, 2) == 0)
		return ("<");
	if (ft_strncmp(">", line, 2) == 0)
		return (">");
	if (ft_strncmp("<<", line, 3) == 0)
		return ("<<");
	if (ft_strncmp(">>", line, 3) == 0)
		return (">>");
	i = (int)ft_strlen(line);
	if (i > MAXLEN - 3)
		return (line);
	line[i + 1] = '"';
	while (i > 0)
	{
		line[i] = line[i - 1];
		i--;
	}
	line[0] = '"';
	return (line);
}

bool	isoperator(char *line)
{
	if (ft_strncmp("|", line, 2) == 0)
		return (true);
	if (ft_strncmp("<", line, 2) == 0)
		return (true);
	if (ft_strncmp(">", line, 2) == 0)
		return (true);
	if (ft_strncmp("<<", line, 3) == 0)
		return (true);
	if (ft_strncmp(">>", line, 3) == 0)
		return (true);
	return (false);
}

void	wordsplit(char *s, t_data *data)
{
	int		i;
	int		j;
	char	line[MAXLEN];

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] == '"' && skipquote(s, &i, '"', data)) \
		|| (s[i] == '\'' && skipquote(s, &i, '\'', data)))
			continue ;
		ft_bzero(line, sizeof(char) * MAXLEN);
		j = -1;
		while (++j >= 0 && s[i + j] && s[i + j] != ' ')
			line[j] = s[i + j];
		if (isoperator(line))
			data->cmd[data->itr++] = ft_strdup(tranform(line));
		else
			data->cmd[data->itr++] = ft_strdup(line);
		if (j > 0)
			i += j;
		else
			i++;
	}
}

// void	filldata(t_data *data, char (*copy)[MAXLEN], int i, int *j)
// {
// 	char	**tkn;
// 	int		k;
// 	int		a[2];
// 	char	line[MAXEXP];

// 	ft_bzero(a, sizeof(int) * 2);
// 	ft_bzero(line, sizeof(char) * MAXEXP);
// 	exptkn(copy[i], a, line, data);
// 	k = -1;
// 	tkn = ft_split(line, ' ');
// 	while (tkn[++k])
// 	{
// 		data->cmd[*j] = tkn[k];
// 		(*j)++;
// 	}
// 	free(tkn);
// }
