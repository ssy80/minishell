/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:42:39 by ssian             #+#    #+#             */
/*   Updated: 2024/10/16 14:19:32 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	print_error_heredoc(void)
{
	ft_putstr_fd("here doc: ", STDERR_FILENO);
	ft_putstr_fd("here doc failed !\n", STDERR_FILENO);
}

void	warning_heredoc_eof(char *delimiter)
{
	ft_putstr_fd("here-document delimited by end-of-file (wanted ",
		STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd(")\n", STDERR_FILENO);
}

char	*get_tmp_file(int i)
{
	char	*tmp_file;
	char	*file;

	file = ft_itoa(i);
	tmp_file = ft_strjoin("/tmp/", file);
	if (tmp_file == NULL)
	{
		print_error_heredoc();
		return (free(file), NULL);
	}
	free(file);
	return (tmp_file);
}

void	handle_sig_child(int sig)
{
	if (sig == SIGINT)
	{
		cleanup_child(NULL);
		signal(SIGINT, SIG_DFL);
		kill(getpid(), SIGINT);
	}
}

void	handle_sigint_parent(int sig)
{
	(void)sig;
}
