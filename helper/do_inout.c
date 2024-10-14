/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_inout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:47:02 by ssian             #+#    #+#             */
/*   Updated: 2024/10/14 15:34:52 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

/* 2 = infile */
static void	do_infile(t_inout *inout, t_data *data)
{
	int	filefd;

	filefd = open(inout->file, O_RDONLY);
	if (filefd < 0)
	{
		perror(inout->file);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	dup2(filefd, STDIN_FILENO);
	close (filefd);
}

/* 0 = create */
static void	do_create(t_inout *inout, t_data *data)
{
	int	filefd;

	filefd = open(inout->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (filefd < 0)
	{
		perror(inout->file);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	dup2(filefd, STDOUT_FILENO);
	close (filefd);
}

/* 1 = append */
static void	do_append(t_inout *inout, t_data *data)
{
	int	filefd;

	filefd = open(inout->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (filefd < 0)
	{
		perror(inout->file);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	dup2(filefd, STDOUT_FILENO);
	close (filefd);
}

/* 3 = heredoc */
static void	do_heredochere(t_inout *inout, t_data *data)
{
	int	filefd;

	filefd = open(inout->heredoc, O_RDONLY);
	if (filefd < 0)
	{
		perror(inout->heredoc);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	unlink(inout->heredoc);
	dup2(filefd, STDIN_FILENO);
	close (filefd);
}

void	do_inout(t_list *inout_list, t_data *data)
{
	t_inout	*inout;

	while (inout_list != NULL)
	{
		inout = (t_inout *)(inout_list->content);
		if (inout->type == 2)
			do_infile(inout, data);
		else if (inout->type == 0)
			do_create(inout, data);
		else if (inout->type == 1)
			do_append(inout, data);
		else if (inout->type == 3)
			do_heredochere(inout, data);
		inout_list = inout_list->next;
	}
}
