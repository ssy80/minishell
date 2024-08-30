/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:51:40 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 12:25:22 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	return (0);
}
/*int main(void)
{
	printf("ft_isprint %d \n", ft_isprint(127));
	printf("isprint %d \n", isprint(127));
	printf("ft_isprint %d \n", ft_isprint('a'));
	printf("isprint %d \n", isprint('a'));
	printf("ft_isprint %d \n", ft_isprint(32));
	printf("isprint %d \n", isprint(32));
	printf("ft_isprint %d \n", ft_isprint('~'));
	printf("isprint %d \n", isprint('~'));
	printf("ft_isprint %d \n", ft_isprint('\n'));
	printf("isprint %d \n", isprint('\n'));
}*/
