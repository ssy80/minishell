/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:07:29 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 13:08:21 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *str_, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)str_;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (str_);
}
/*int main(void)
{
	char str[] = "hello world 42 Singapore";
	ft_memset(&str, '$', 1);
	printf("ft_memset %s \n", str);
	char str1[] = "hello world 42 Singapore";
	memset(&str1, '$', 1);
	printf("memset %s \n", str1);
	return (0);
}*/
