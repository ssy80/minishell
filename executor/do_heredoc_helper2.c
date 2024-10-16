/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc_helper2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:43:02 by ssian             #+#    #+#             */
/*   Updated: 2024/10/16 14:17:58 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	clean(t_heredoc *heredoc)
{
	close(heredoc->filefd);
	unlink(heredoc->file);
	free(heredoc->file);
	free(heredoc->delimiter);
	close(heredoc->pipefd[1]);
	free_all2(heredoc->data);
	heredoc->data = NULL;
	heredoc->file = NULL;
	heredoc->pipefd = NULL;
	heredoc->delimiter = NULL;
}

void	cleanup_child(t_heredoc *heredoc)
{
	static t_heredoc	*tmp_heredoc;

	if (heredoc == NULL)
	{
		if (tmp_heredoc != NULL)
		{
			printf("\n");
			clean(tmp_heredoc);
		}
	}
	else
		tmp_heredoc = heredoc;
}

char	*get_delimiter(char *inout_delimiter, int got_quotes)
{
	t_stack	stack;
	char	*delimiter;

	ft_bzero(&stack, sizeof(t_stack));
	if (got_quotes == 1)
	{
		qremoval(inout_delimiter, &stack);
		delimiter = ft_strdup(stack.line);
		if (delimiter == NULL)
			return (NULL);
	}
	else
	{
		delimiter = ft_strdup(inout_delimiter);
		if (delimiter == NULL)
			return (NULL);
	}
	return (delimiter);
}

void	close_free_heredoc(t_heredoc *heredoc)
{
	close(heredoc->filefd);
	free(heredoc->delimiter);
	free(heredoc->file);
	free_all2(heredoc->data);
	close(heredoc->pipefd[1]);
}

void	save_heredoc_file(int pipefd[2], t_inout *inout)
{
	char	*tmp_file;

	tmp_file = malloc(10 * sizeof(char));
	ft_bzero(tmp_file, 10);
	read(pipefd[0], tmp_file, 10);
	inout->heredoc = tmp_file;
	close(pipefd[0]);
}
