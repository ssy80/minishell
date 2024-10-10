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

#include "../minishell.h"

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
}

bool	outer2q(char *s)
{
	int	i;
	int count;

	i = -1;
	count = 0;
	if (s[0] == '"' || s[0] == '\'')
	{
		while (s[++i])
		{
			if (s[0] == s[i])
				count++;
		}
	}
	if (count == 2 && s[i - 1] == s[0])
		return (true);
	return (false);
}

void	filldata(t_data *data, char (*copy)[MAXLEN], int i, int *j)
{
	char	**tkn;
	int		k;
	int		a[2];
	char	line[MAXEXP];

	ft_bzero(a, sizeof(int) * 2);
	ft_bzero(line, sizeof(char) * MAXEXP);
	exptkn(copy[i], a, line, data);
	k = -1;
	tkn = ft_split(line, ' ');
	while (tkn[++k])
	{
		data->cmd[*j] = tkn[k];
		(*j)++;
	}
	free(tkn);
}

void expandclone(t_data *data)
{
	int	i;
	int	j;
	char copy[MAXLEN][MAXLEN];

	clonetkn(copy, data);
	free_datacmd(data);
	i = -1;
	j = 0;

	while (copy[++i][0])
	{
		if (ignoreexp(copy[i]) || ignoreexp2(copy[i]))
			data->cmd[j++] = ft_strdup(copy[i]);
		else if (outer2q(copy[i]))
			data->cmd[j++] = expand1tkn(copy[i], data);
		else
			filldata(data, copy, i, &j);
	}
}
