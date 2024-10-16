/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:22:20 by ssian             #+#    #+#             */
/*   Updated: 2024/10/16 14:09:19 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

/* dir is the cwd + :  eq the prompt to print*/
void	getprompt(char *dir)
{
	int	i;

	ft_bzero(dir, sizeof(char) * MAXLEN);
	getcwd(dir, sizeof(char) * MAXLEN);
	i = ft_strlen(dir);
	if (MAXLEN - 2 < i)
	{
		*dir = 0;
		return ;
	}
	dir[i] = ':';
	dir[i + 1] = ' ';
	dir[i + 2] = '\0';
}

// get input from user
int	getcmd(char *buf, int size, char *dir, t_data *data)
{
	char		*input;
	int			len;

	ft_bzero(buf, size);
	ft_bzero(data->tkn, MAXLEN * 2);
	ft_bzero(data->cmd, sizeof(char *) * MAXLEN);
	data->itr = 0;
	data->tkn_no = 0;
	getprompt(dir);
	if (!dir)
		return (ft_putstr_fd("dir too long to print\n", 1), -1);
	input = readline(dir);
	if (!input)
		return (freenullall(data), -1);
	len = ft_strlen(input);
	if (len > size - 1)
		return (ft_putstr_fd("str too long\n", 1), freenull(input), 0);
	if (is_spaces(input) == 0)
	{
		ft_strlcpy(buf, input, len + 1);
		add_history(buf);
	}
	return (freenull(input), 0);
}

void	error_main(t_data *data)
{
	free_datacmd(data);
	freenullall(data);
	exit(EXIT_FAILURE);
}

void	free_main_last(t_list *cmd_list, t_data *data)
{
	free_cmdlist(cmd_list);
	ft_freelist(cmd_list);
	free_datacmd(data);
}

int	do_expander(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->itr)
	{
		if (expander(data->cmd[i], data, i) == 0)
			return (0);
		i++;
	}
	return (1);
}
