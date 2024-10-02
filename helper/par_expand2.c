/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_expand2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:16:10 by yoong             #+#    #+#             */
/*   Updated: 2024/10/02 13:16:20 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exptkn(char *s, int a[2], char *line, t_data *data)
{
	while (s[a[0]])
	{
		if (s[a[0]] == '\'')
			return (a[0]++, exp1q(s, a, line, data), exptkn(s, a, line, data));
		if (s[a[0]] == '"')
			return (a[0]++, exp2q(s, a, line, data), exptkn(s, a, line, data));
		if (s[a[0]] == '$')
			return (a[0]++, exp_s(s, a, line, data), exptkn(s, a, line, data));
		line[a[1]] = s[a[0]];
		a[0]++;
		a[1]++;
	}
}

int	expander(char *s, t_data *data, int i)
{
	int		a[2];
	char	line[MAXEXP];
	char	*str;

	ft_bzero(a, sizeof(int) * 2);
	ft_bzero(line, sizeof(char) * MAXEXP);
	exptkn(s, a, line, data);
	str = ft_strdup(line);
	if (str == NULL)
		return (0);
	free(data->cmd[i]);
	data->cmd[i] = str;
	return (1);
}
