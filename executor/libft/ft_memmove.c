/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:14:28 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 13:06:58 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*ref: https://stackoverflow.com/questions/77108521
/mimicking-memmoves-behaviour */
/*need reverse copy to prevent data corruption*/
void	*ft_memmove(void *dest_, const void *src_, size_t n)
{
	size_t	i;
	char	*dest;
	char	*src;

	if (dest_ == NULL && src_ == NULL)
		return (dest_);
	dest = (char *)dest_;
	src = (char *)src_;
	if (dest > src)
	{
		i = n;
		while (i--)
			dest[i] = src[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (dest);
}
/*int	main(void)
{
	//char dest1[] = "hello world!";
	//const char src1[] = "aaaaaaaa";
	//char *d1 = ft_memmove(&dest1, &src1, 0);
	//printf("d1d1d1d1d1 %s \n", d1);
	//printf("ft_memmove %s \n", dest1);
	
	char dest2[] = "hello world!";
	const char src2[] = "aaaaaaaa";
	char *d2 = memmove(&dest2, &src2, 0);
	printf("d2d2d2d2d2 %s \n", d2);
	printf("___memmove %s \n", dest2);
	//fn1();

	char *src = "thanks to @apellicc for this test !\r\n";
	char dst1[0xF0];
	int size = strlen(src);
	char *r1 = memmove(dst1, src, size);
	//char *r2 = ft_memmove(dst1, src, size);
	puts(r1);
	//puts(r2);

	char csrc[8] = "Geeksfor";
	char csrc2[8] = "Geeksfor";
	char *ds1 = ft_memmove(csrc+5, csrc, 2);
	printf("1 %s \n", csrc);
	printf("1 %s \n", ds1);
	char *ds2 = memmove(csrc2+5, csrc2, 2);
	printf("2 %s \n", csrc2);
	printf("2 %s \n", ds2);
	//fn2();
}*/
