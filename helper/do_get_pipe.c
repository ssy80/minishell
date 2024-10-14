/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_get_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:08:58 by ssian             #+#    #+#             */
/*   Updated: 2024/10/14 15:39:20 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	free_pipefd(int **pipefd, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(pipefd[j]);
		j++;
	}
	free(pipefd);
}

static void	print_error_pipe(void)
{
	ft_putstr_fd("pipe: ", STDERR_FILENO);
	ft_putstr_fd("create pipe failed !\n", STDERR_FILENO);
}

int	**get_pipe(int size)
{
	int	**pipefd;
	int	i;

	pipefd = malloc(sizeof(int *) * size);
	if (pipefd == NULL)
		return (print_error_pipe(), NULL);
	ft_bzero(pipefd, sizeof(int *) * size);
	i = 0;
	while (i < size)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		if (pipefd[i] == NULL)
		{
			free_pipefd(pipefd, i);
			return (print_error_pipe(), NULL);
		}
		ft_bzero(pipefd[i], sizeof(int) * 2);
		i++;
	}
	return (pipefd);
}
