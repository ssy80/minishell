/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:46:17 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 16:01:05 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c = c + 32;
	return (c);
}
/*int	main(void)
{
	printf("ft_tolower %c \n", ft_tolower('A'));
	printf("tolower %c \n", tolower('A'));
	printf("ft_tolower %c \n", ft_tolower('Z'));
	printf("tolower %c \n", tolower('Z'));
	printf("ft_tolower %c \n", ft_tolower(88));
	printf("tolower %c \n", tolower(88));
	printf("ft_tolower %c \n", ft_tolower('s'));
	printf("tolower %c \n", tolower('s'));
	printf("ft_tolower %c \n", ft_tolower('1'));
	printf("tolower %c \n", tolower('1'));
	printf("ft_tolower %c \n", ft_tolower('\n'));
	printf("tolower %c \n", tolower('\n'));
}*/
