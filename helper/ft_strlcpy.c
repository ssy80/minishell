/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:07:11 by yoong             #+#    #+#             */
/*   Updated: 2024/03/04 17:28:32 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	n;
	size_t	j;

	n = 0;
	j = 0;
	while (src[n] != '\0')
		n++;
	if (size < 1)
		return (n);
	while (src[j] && j < size - 1)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (n);
}
