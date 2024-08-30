/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:32:57 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 16:01:32 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c = c - 32;
	return (c);
}
/*int	main(void)
{
	printf("ft_toupper %c \n", ft_toupper('a'));
	printf("toupper %c \n", toupper('a'));
    printf("ft_toupper %c \n", ft_toupper('z'));
	printf("toupper %c \n", toupper('z'));
	printf("ft_toupper %c \n", ft_toupper(88));
	printf("toupper %c \n", toupper(88));
	printf("ft_toupper %c \n", ft_toupper('\n'));
	printf("toupper %c \n", toupper('\n'));
	printf("ft_toupper %c \n", ft_toupper('S'));
	printf("toupper %c \n", toupper('S'));
	printf("ft_toupper %c \n", ft_toupper('u'));
	printf("toupper %c \n", toupper('u'));
}*/
