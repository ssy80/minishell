/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 09:12:08 by yoong             #+#    #+#             */
/*   Updated: 2024/08/09 09:12:10 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	copyenv(char **env, t_data *data)
{
	int	i;
	int	len;

	i = 0;
	while (env[i])
		i++;
	data->env = ft_calloc(i + 1, sizeof(char *));
	if (!data->env)
		return (ft_putstr_fd(MFAIL, 1), exit(1));
	setfreept(data, data->env);
	i = -1;
	while (env[++i])
	{
		len = ft_strlen(env[i]);
		data->env[i] = ft_calloc(len + 1, sizeof(char));
		if (!data->env[i])
			return (ft_putstr_fd(MFAIL, 1), freenullall(data), exit(1));
		setfreept(data, data->env[i]);
		ft_strlcpy(data->env[i], env[i], len + 1);
	}
}

void	initdata(char buf[MAXLEN], char **env, t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->buf = buf;
	copyenv(env, data);
}
