/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:58:25 by ssian             #+#    #+#             */
/*   Updated: 2024/05/23 14:32:21 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*  count len(i) of dest is < buffer size(dest) 
    to check whether can concat. 
     e.g ft_strlcat(dest[10]="hello", "world", 10) 
	     in this case len(i) will be 5, can concat 
		 another 4 + 1('\0).
	 size > i (means can concat the src up to size -1) 
	 and return (len(i) + strlen(src)) = 5 + 5 =10
	 else if(size == i || size < i) (means cannot concat any src) 
	 thus just return (strlen(src) + size)
	 if size > i, proceed to concat the src to dest.
	 This (i + 1 < size) is to concat with at least 
	 1 char left for the null terminator
	 */
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ret_size;

	i = 0;
	while ((dest[i] != '\0') && (i < size))
		i++;
	if (i < size)
		ret_size = i + ft_strlen(src);
	else
	{
		ret_size = ft_strlen(src) + size;
		return (ret_size);
	}
	j = 0;
	while ((i + 1 < size) && (src[j] != '\0') && (size != 0))
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (ret_size);
}
/*int main(void)
{
	char a[10]="hello";
	int j = 0;
	const char s[]="world!";
	int i = strlcat(a,s,10);
	printf("___strlcat:%d\n", i);
	printf("___strlcat:%s\n", a);
	char a1[10]="hello";
    const char s1[]="world!";
    int ii = ft_strlcat(a1,s1,10);
    printf("ft_strlcat:%d\n", ii);
	printf("ft_strlcat:%s\n", a1);
}*/
