/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:13:08 by ssian             #+#    #+#             */
/*   Updated: 2024/10/14 15:53:06 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int	is_all_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

/*−9223372036854775808, +9223372036854775807 [LLONG_MIN, LLONG_MAX] long long*/
static int	is_valid_code(char *str)
{
	int			zeros;
	int			i;
	long double	code;

	i = 0;
	zeros = 0;
	while (str[i] == '0' || str[i] == '+' || str[i] == '-')
	{
		zeros++;
		i++;
	}
	if ((ft_strlen(str) - zeros) > 19)
		return (0);
	code = ft_atold(str);
	if (code > LLONG_MAX || code < LLONG_MIN)
		return (0);
	return (1);
}

static void	error_need_numeric(char *arg, t_data *data)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free_all(data);
	exit(2);
}

static void	error_many_args(void)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd("too many arguments\n", STDERR_FILENO);
}

int	builtin_exit(char **args, t_data *data)
{
	int			size;
	long long	code;

	size = get_args_len(args);
	if (size == 1)
	{
		free_all(data);
		exit(0);
	}
	if (is_all_digit(args[1]) == 0)
		error_need_numeric(args[1], data);
	if (is_valid_code(args[1]) == 0)
		error_need_numeric(args[1], data);
	if (size > 2)
	{
		error_many_args();
		return (0);
	}
	code = ft_atoll(args[1]);
	if (code > 255)
		code = code % 256;
	free_all(data);
	exit(code);
}
