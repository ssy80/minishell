/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:24:19 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 12:58:53 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str_, int c_, size_t n)
{
	size_t			i;
	unsigned char	c;
	unsigned char	*str;

	i = 0;
	c = (unsigned char)c_;
	str = (unsigned char *)str_;
	while (i < n)
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/*int main(void)
{
	const char str1[] = "hello world!";
	char c1 = 'o';
	char *d1 = ft_memchr(str1, c1, 5);
	printf("ft_memchr %s \n", d1);
	const char str2[] = "hello world!";
	char c2 = 'o';
	char *d2 = memchr(str2, c2, 5);
	printf("ft_memchr %s \n", d2);
}*/
