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
#include "minishell.h"

// copy env into linkedlist for easier manipulation when editing env value
void	copyenv(char **env, t_data *data)
{
	int		i;
	int		len;
	t_list	*ll;
	t_list	*tmp;

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

//  count length of int
int	lenint(int l)
{
	int	i;

	i = 0;
	while (l != 0)
	{
		i++;
		l /= 10;
	}
	return (i);
}

// return SHLVL=l in string form
char	*fillcont(int l)
{
	char	*a;
	int		tmp;

	tmp = lenint(l);
	a = ft_calloc(6 + 1 + tmp, sizeof(char));
	if (!a)
		return (NULL);
	a[6 + tmp] = '\0';
	ft_strlcpy(a, "SHLVL=", 7);
	while (tmp > 0)
	{
		a[6 + tmp - 1] = l % 10 + '0';
		tmp--;
		l /= 10;
	}
	return (a);
}

// increase shlvl
void	addshlvl(t_data *data)
{
	t_list	*cp;
	int		i;
	int		l;

	cp = data->env;
	i = 5;
	l = 0;
	while (cp)
	{
		if (ft_strncmp((char *)cp->content, "SHLVL=", 6) == 0)
		{
			while (((char *)cp->content)[++i])
				l = ((char *)cp->content)[i] - '0' + l * 10;
			free(cp->content);
			cp->content = fillcont(l + 1);
			if (!cp->content)
				return (ft_putstr_fd(MFAIL, 1), freenullall(data), exit(1));
		}
		cp = cp->next;
	}
}

// initializing all variable in data struct to null
// prevent valgrind error of uninitialised value being used
void	initdata(char buf[MAXLEN], char **env, t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->buf = buf;
	copyenv(env, data);
	addshlvl(data);
}
