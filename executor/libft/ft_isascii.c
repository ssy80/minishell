/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:20:24 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 12:23:56 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*int main(void)
{
	printf("ft_isascii %d \n", ft_isascii('A'));
	printf("isascii %d \n", isascii('A'));
	printf("ft_isascii %d \n", ft_isascii('s'));
	printf("isascii %d \n", isascii('s'));
	printf("ft_isascii %d \n", ft_isascii(128));
	printf("isascii %d \n", isascii(128));
	printf("ft_isascii %d \n", ft_isascii('0'));
	printf("isascii %d \n", isascii('0'));
	printf("ft_isascii %d \n", ft_isascii('Z'));
    printf("isascii %d \n", isascii('Z'));
}*/
