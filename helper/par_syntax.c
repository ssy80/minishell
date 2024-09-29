/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:44:25 by yoong             #+#    #+#             */
/*   Updated: 2024/09/14 11:44:30 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// check if the " or ' is being closed 
int	syn_q(char *str, int i, char q)
{
	while (str[i] && str[i] != q)
		i++;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

static void	print_err_nl(void)
{
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	write(STDERR_FILENO, "newline", 7);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

static void	print_err_nl1(char *s)
{
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	write(STDERR_FILENO, s, 1);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

// check if the tkn is cmd
bool	syn_str(t_data *data, int i)
{
	int	j;
	int	res;

	j = 0;
	if (!data->cmd[i])
		return (print_err_nl(), false);
	if (is_sym(data->cmd[i][j]))
		return (print_err_nl1(&data->cmd[i][j]), false);
	while (data->cmd[i][j])
	{
		if (data->cmd[i][j] == '\'' || data->cmd[i][j] == '"')
		{
			res = syn_q(data->cmd[i], j + 1, data->cmd[i][j]);
			if (res < 0)
				return (print_err_nl1(&data->cmd[i][j]), false);
			j = res;
		}
		j++;
	}
	return (true);
}

// check if the sym is <, >, <<, >>
bool	is_redirsym(char *s)
{
	if (!s)
		return (false);
	if (ft_strncmp("<", s, 2) == 0 || ft_strncmp(">", s, 2) == 0)
		return (true);
	if (ft_strncmp("<<", s, 3) == 0 || ft_strncmp(">>", s, 3) == 0)
		return (true);
	return (false);
}

// check if the sym is |
bool	is_pipesym(char *s)
{
	if (!s)
		return (false);
	if (ft_strncmp("|", s, 2) == 0)
		return (true);
	return (false);
}

static void	print_err_pipe(void)
{
	ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd("|", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

bool	syn_check(t_data *data)
{
	int	i;

	i = -1;
	while (data->cmd[++i])
	{
		if (i == 0 && ft_strncmp("|", data->cmd[i], 2) == 0)
			return (print_err_pipe(), false);
		else if (is_redirsym(data->cmd[i]))
		{
			if (!data->cmd[i + 1] || ft_strncmp("|", data->cmd[i + 1], 2) == 0)
				return (syn_str(data, i + 1));
		}
		else if (is_pipesym(data->cmd[i]))
		{
			if (!data->cmd[i + 1] || ft_strncmp("|", data->cmd[i + 1], 2) == 0)
				return (print_err_pipe(), false);
		}
		else if (!syn_str(data, i))
			return (false);
	}
	return (true);
}
