/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:46:25 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 13:04:25 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest_, const void *src_, size_t n)
{
	size_t	i;
	char	*dest;
	char	*src;

	if (dest_ == NULL && src_ == NULL)
		return (dest_);
	i = 0;
	dest = (char *)dest_;
	src = (char *)src_;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest_);
}
/*int	main(void)
{
	const char src1[] = "hello world";
	char dest1[] = "aaaaaaaaaabbbbbbbbbb";
	char *d1 = ft_memcpy(dest1, src1, 0);
	printf("ft_memcpy %s \n", dest1);
	printf("ft_memcpy %s \n", d1);
	const char src2[] = "hello world";
	char dest2[] = "aaaaaaaaaabbbbbbbbbb";
	char *d2 = memcpy(dest2, src2, 0);
	printf("memcpyddd %s \n", dest2);
	printf("ddddddddd %s \n", d2);
	char *d3 = ft_memcpy(((void*)0), ((void*)0), 3);
	printf("ft_memcpy %s \n", d3);
	//char *d4 = memcpy(((void*)0), ((void*)0), 3);
	//printf("memcpy %s \n", d4);
}*/
