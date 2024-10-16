/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:20:55 by ssian             #+#    #+#             */
/*   Updated: 2024/10/16 14:17:03 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	heredoc_child(t_inout *inout, int i, int *pipefd, t_data *data)
{
	int			got_quotes;
	t_heredoc	heredoc;

	ft_bzero(&heredoc, sizeof(t_heredoc));
	got_quotes = is_contain_quotes(inout->delimiter);
	heredoc.delimiter = get_delimiter(inout->delimiter, got_quotes);
	if (heredoc.delimiter == NULL)
		return (print_error_heredoc(), exit(EXIT_FAILURE));
	heredoc.file = get_tmp_file(i);
	if (heredoc.file == NULL)
		return (print_error_heredoc(),
			free(heredoc.delimiter), exit(EXIT_FAILURE));
	heredoc.filefd = open(heredoc.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc.filefd < 0)
		return (print_error_heredoc(), free(heredoc.file),
			free(heredoc.delimiter), exit(EXIT_FAILURE));
	heredoc.data = data;
	heredoc.pipefd = pipefd;
	cleanup_child(&heredoc);
	do_readline(heredoc.delimiter, heredoc.filefd, got_quotes, data);
	write(pipefd[1], heredoc.file, strlen(heredoc.file) + 1);
	close_free_heredoc(&heredoc);
}

static int	wait_heredoc_child(int pipefd[2], t_data *data, t_inout *inout)
{
	int	status;

	status = 0;
	close(pipefd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait(&status);
	if (WIFSIGNALED(status))
	{
		close(pipefd[0]);
		update_exit_status(128 + WTERMSIG(status), data);
		return (-9);
	}
	else if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
		{
			save_heredoc_file(pipefd, inout);
			update_exit_status(WEXITSTATUS(status), data);
		}
		else
			return (close(pipefd[0]), WEXITSTATUS(status));
	}
	return (1);
}

static int	do_heredoc_as_child(t_inout *inout, int i, t_data *data)
{
	int		pipefd[2];
	pid_t	pidt;

	if (pipe(pipefd) == -1)
		return (perror("pipe failed!"), 0);
	pidt = fork();
	if (pidt == -1)
		return (perror("fork failed!"), 0);
	if (pidt == 0)
	{
		close(pipefd[0]);
		signal(SIGINT, handle_sig_child);
		signal(SIGQUIT, SIG_IGN);
		heredoc_child(inout, i, pipefd, data);
		exit(0);
	}
	else
		return (wait_heredoc_child(pipefd, data, inout));
	return (1);
}

int	do_heredoc(t_list *cmd_list, t_data *data)
{
	t_list	*inout_list;
	t_inout	*inout;
	int		i;
	int		heredoc_status;

	i = 0;
	while (cmd_list != NULL)
	{
		inout_list = ((t_cmd *)(cmd_list->content))->inout_list;
		while (inout_list != NULL)
		{
			inout = (t_inout *)(inout_list->content);
			if (inout->type == 3)
			{
				heredoc_status = 0;
				heredoc_status = do_heredoc_as_child(inout, i, data);
				if (heredoc_status <= 0)
					return (heredoc_status);
			}
			i++;
			inout_list = inout_list->next;
		}
		cmd_list = cmd_list->next;
	}
	return (1);
}
