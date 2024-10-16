/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list_helper4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:41:21 by ssian             #+#    #+#             */
/*   Updated: 2024/10/16 11:23:36 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	is_valid_to_expand(char *str)
{
	int	i;

	if (is_contain(str, 39) == 0 && is_contain(str, 34) == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != 39 && str[i] != 34
			&& str[i] != '|' && str[i] != '>' && str[i] != '<')
			return (0);
		i++;
	}
	return (1);
}

int	is_operator_in_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 39 && str[i] != 34)
		{
			if (str[i] == '|' && (str[i + 1] == 39 || str[i + 1] == 34))
				return (1);
			if (str[i] == '>' && (str[i + 1] == 39 || str[i + 1] == 34))
				return (1);
			if (str[i] == '<' && (str[i + 1] == 39 || str[i + 1] == 34))
				return (1);
			if (str[i] == '>' && str[i + 1] == '>'
				&& ((str[i + 2] == 39 || str[i + 2] == 34)))
				return (1);
			if (str[i] == '<' && str[i + 1] == '<'
				&& ((str[i + 2] == 39 || str[i + 2] == 34)))
				return (1);
			break ;
		}
		i++;
	}
	return (0);
}

int	expand_str(int i, t_data *data)
{
	char	*exp_arg;

	if (is_valid_to_expand(data->cmd[i]) == 0)
		return (1);
	if (is_operator_in_quotes(data->cmd[i]) == 0)
		return (1);
	exp_arg = expand1tkn(data->cmd[i], data);
	if (exp_arg == NULL)
		return (0);
	free(data->cmd[i]);
	data->cmd[i] = exp_arg;
	return (1);
}
