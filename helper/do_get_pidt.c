/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_get_pidt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:12:32 by ssian             #+#    #+#             */
/*   Updated: 2024/10/14 15:23:25 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	print_error_pidt(void)
{
	ft_putstr_fd("pidt: ", STDERR_FILENO);
	ft_putstr_fd("create pidt failed !\n", STDERR_FILENO);
}

pid_t	*get_pidt(int size)
{
	pid_t	*pidt;

	pidt = malloc(sizeof(pid_t) * size);
	if (pidt == NULL)
		return (print_error_pidt(), NULL);
	ft_bzero(pidt, sizeof(pid_t) * size);
	return (pidt);
}
