/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:45:09 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 16:58:54 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	if (n == 0)
		return (ft_strlen(src));
	i = 0;
	while ((i < (n - 1)) && (src[i] != '\0') && n != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
/*int	main(void)
{
	char dest1[20];
	char src1[] = "hellohellohellohelloaa";
	int i = ft_strlcpy(dest1, src1, 20);
	printf("ft_strlcpy %d \n", i);
	puts(dest1);
	char dest2[20];
	char src2[] = "hellohellohellohelloaa";
	int j = strlcpy(dest2, src2, 20);
	printf("strlcpy %d \n", j);
	puts(dest2);
}*/
