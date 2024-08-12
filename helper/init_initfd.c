/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initfd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:35:25 by yoong             #+#    #+#             */
/*   Updated: 2024/08/04 13:35:32 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// used for opening fd 0, 1 and 2
void	initfd(char *dir)
{
	int	fd;

	getprompt(dir);
	fd = open("console", O_RDWR);
	while (fd >= 0)
	{
		if (fd >= 3)
		{
			close(fd);
			break ;
		}
		fd = open("console", O_RDWR);
	}
}
