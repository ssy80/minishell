/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 09:45:57 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 13:03:10 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1_, const void *s2_, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	s1 = (unsigned char *)s1_;
	s2 = (unsigned char *)s2_;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
/*int	main(void)
{
	char s1[] = "hello";
	char s2[] = "hellzz";
	printf("ft_memcmp %d \n", ft_memcmp(s1, s2, 1));
	printf("___memcmp %d \n", memcmp(s1, s2, 1));
	printf("ft_memcmp %d \n", ft_memcmp(s1, s2, 0));
	printf("___memcmp %d \n", memcmp(s1, s2, 0));
	printf("ft_memcmp %d \n", ft_memcmp(s1, s2, 5));
	printf("___memcmp %d \n", memcmp(s1, s2, 5));
	printf("ft_memcmp %d \n", ft_memcmp(s1, s2, 6));
	printf("___memcmp %d \n", memcmp(s1, s2, 6));
}*/
