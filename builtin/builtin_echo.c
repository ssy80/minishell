/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:12:05 by ssian             #+#    #+#             */
/*   Updated: 2024/10/14 15:48:19 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*is valid option -n -nnnnn -nnn*/
static int	is_valid_option(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	if (starts_with(str, "-n") == 1)
	{
		i = 1;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	builtin_echo(char **args)
{
	int	i;
	int	flag_n;

	flag_n = 1;
	i = 1;
	if (is_valid_option(args[i]) == 1)
	{
		flag_n = 0;
		i++;
	}
	while (args[i])
	{
		if (is_valid_option(args[i]) == 0)
			break ;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (flag_n == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
