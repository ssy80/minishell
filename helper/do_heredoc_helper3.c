/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc_helper3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 23:13:31 by ssian             #+#    #+#             */
/*   Updated: 2024/10/16 14:18:42 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	write_line(int got_quotes, char *line, t_data *data, int filefd)
{
	t_stack	stack;

	ft_bzero(&stack, sizeof(t_stack));
	if (got_quotes == 0)
	{
		expandss(&stack, line, data);
		write(filefd, stack.line, ft_strlen(stack.line));
	}
	else
		write(filefd, line, ft_strlen(line));
	write(filefd, "\n", 1);
}

void	do_readline(char *delimiter, int filefd, int got_quotes, t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			warning_heredoc_eof(delimiter);
			break ;
		}
		if (equals(line, delimiter) == 1)
		{
			free(line);
			break ;
		}
		write_line(got_quotes, line, data, filefd);
		free(line);
	}
}
