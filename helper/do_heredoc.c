/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:20:55 by ssian             #+#    #+#             */
/*   Updated: 2024/09/27 23:21:01 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void print_error_heredoc()
{
    ft_putstr_fd("here doc: ", STDERR_FILENO);
    ft_putstr_fd("here doc failed !\n", STDERR_FILENO);
}

static char *get_tmp_file(int i)
{
    char *tmp_file;
    char *file;

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

int do_heredoc(t_inout *inout, int i)
{
	char	*line;
	char	*tmp_file;
	int		filefd;

	tmp_file = get_tmp_file(i);
	if (tmp_file == NULL)
		return (0);
	filefd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (filefd < 0)
		return (print_error_heredoc(), free(tmp_file), 0);
	while ((line = readline("> ")) != NULL) 
	{
		if (equals(line, inout->delimiter) == 1)
		{
			free(line);
			break;
		}
		write(filefd, line, ft_strlen(line));
		write(filefd, "\n", 1);
		free(line);
	}
	close(filefd);
	inout->heredoc = tmp_file;
	return (1);
}