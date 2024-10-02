/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_func2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:37:53 by yoong             #+#    #+#             */
/*   Updated: 2024/10/02 13:37:59 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	listlength(t_list *a)
{
	int	i;

	i = 0;
	while (a)
	{
		a = a->next;
		i++;
	}
	return (i);
}

void	exitcommand(char *input, t_data *data)
{
	char	**arr;
	bool	e;
	int		i;

	e = false;
	if (!input[0])
		return ;
	arr = ft_split(input, ' ');
	if (!arr)
		return (freenull(input), exitcl(1));
	if (ft_strncmp(arr[0], "exit", 4) == 0)
		e = true;
	if (ft_strlen(arr[0]) != 4)
		e = false;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	if (e)
		return (freenullall(data), freenull(input), exitcl(0));
}

void	getpwd(void)
{
	char	tmp[MAXLEN];

	getcwd(tmp, sizeof(char) * MAXLEN);
	ft_putstr_fd(tmp, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	getcd(char *buf)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(buf + 3, ' ');
	while (tmp[i])
		i++;
	if (i == 0)
		ft_putstr_fd("", STDOUT_FILENO);
	else if (i > 1)
		ft_putstr_fd("cd: too many arguments\n", STDOUT_FILENO);
	else if (chdir(tmp[0]) < 0)
		ft_putstr_fd(CDERR, STDERR_FILENO);
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
}

// env, cd, pwd
int	builtin_func(char *buf, t_data *data)
{
	if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == '\0')
		return (ft_putstr_fd("", STDOUT_FILENO), 0);
	if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		return (getcd(buf), 0);
	if (buf[0] == 'p' && buf[1] == 'w' && buf[2] == 'd' \
	&& (buf[3] == ' ' || buf[3] == '\0'))
		return (getpwd(), 0);
	if (buf[0] == 'e' && buf[1] == 'n' && buf[2] == 'v' \
	&& (buf[3] == ' ' || buf[3] == '\0'))
		return (getmyenv(data), 0);
	return (1);
}
