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
#include "minishell.h"

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

// get env value with var as key
char	*getenvvar(char *var, t_data *data)
{
	size_t	i;
	t_list	*cp;

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
			return (&((char *)cp->content)[i + 1]);
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
	if (var[i] != '_' && ft_isalpha(var[i]) == 0)
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
		return (free(tmp), ft_putstr_fd(MFAIL, 1), freenullall(data), \
		exit(1), -1);
	ft_lstadd_back(&(data->env), envnode);
	return (0);
}

void	lltoarray(t_data *data)
{
	int		i;
	t_list	*cp;

	i = -1;
	data->envc = ft_calloc(listlength(data->env) + 1, sizeof(char *));
	if (!data->envc)
		return (ft_putstr_fd(MFAIL, 1), freenullall(data), exit(1));
	cp = data->env;
	while (cp)
	{
		data->envc[++i] = data->env->content;
		cp = data->env->next;
	}
}
