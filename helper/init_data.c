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

// void	copyenv1(char **env, t_data *data)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	data->env = ft_calloc(i + 1, sizeof(char *));
// 	if (!data->env)
// 		return (ft_putstr_fd(MFAIL, 1), exit(1));
// 	setfreept(data, data->env);
// 	i = -1;
// 	while (env[++i])
// 	{
// 		len = ft_strlen(env[i]);
// 		data->env[i] = ft_calloc(len + 1, sizeof(char));
// 		if (!data->env[i])
// 			return (ft_putstr_fd(MFAIL, 1), freenullall(data), exit(1));
// 		setfreept(data, data->env[i]);
// 		ft_strlcpy(data->env[i], env[i], len + 1);
// 	}
// }

static void	copyenv(char **env, t_data *data)
{
	int		i;
	int		len;
	t_list*	ll;
	t_list*	tmp;

	i = -1;
	len = 0;
	ll = NULL;
	tmp = NULL;
	while (env[++i])
	{
		len = ft_strlen(env[i]);
		tmp = ft_lstnew(ft_calloc(len + 1, sizeof(char)));
		if (!tmp || !tmp->content)
			return (ft_putstr_fd(MFAIL, 1), ft_lstclear(&ll, free), \
			free(tmp), freenullall(data), exit(1));
		ft_strlcpy(tmp->content, env[i], len + 1);
		ft_lstadd_back(&ll, tmp);
	}
	data->env = ll;
}

void	initdata(char buf[MAXLEN], char **env, t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->buf = buf;
	copyenv(env, data);
}
