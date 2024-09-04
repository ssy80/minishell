/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_func.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:31:42 by yoong             #+#    #+#             */
/*   Updated: 2024/08/04 11:31:44 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	getpwd(void)
{
	char	tmp[MAXLEN];

	getcwd(tmp, sizeof(char) * MAXLEN);
	ft_putstr_fd(tmp, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	getmyenv(t_data *data)
{
	t_list	*cp;

	cp = data->env;
	while (cp)
	{
		ft_putstr_fd(cp->content, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		cp = cp->next;
	}
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

// get env value with var as key
char	*getenvvar(char *var, t_data *data)
{
	size_t	i;
	t_list *cp;
	
	cp = data->env;
	while (cp)
	{
		i = -1;
		while (var[++i])
		{
			if (((char *)cp->content)[i] != var[i])
				break ;
		}
		if (i == ft_strlen(var) && ((char *)cp->content)[i] == '=' && !var[i])
			return (&((char *)cp->content)[i+1]);
		cp = cp->next;
	}
	return ("");
}

/* 
	return false if 

 */
bool	isvalidenvkey(char *var)
{
	int	i;

	i = 0;
	if (var[i] != '_' && ft_isalpha(var[i]) ==0)
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (var[i] != '_' && ft_isalnum(var[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}


int	addenvvar(char *var, t_data *data)
{
	char	*tmp;
	size_t	l;
	t_list	*envnode;

	l = ft_strlen(var);
	tmp = ft_calloc(l + 1, sizeof(char));
	if (!tmp)
		return (ft_putstr_fd(MFAIL, 1), freenullall(data), exit(1), -1);
	ft_strlcpy(tmp, var, l + 1);
	envnode = ft_lstnew(tmp);
	if (!envnode)
		return (free(tmp), ft_putstr_fd(MFAIL, 1), freenullall(data), exit(1), -1);
	ft_lstadd_back(&(data->env), envnode);
	return (0);
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
