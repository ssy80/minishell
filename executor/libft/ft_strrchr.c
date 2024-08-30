/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:19:09 by ssian             #+#    #+#             */
/*   Updated: 2024/05/23 14:33:09 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str_, int c)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (c >= 256)
		c = c % 256;
	str = (char *)str_;
	i = ft_strlen(str_);
	j = i;
	i++;
	while (i != 0)
	{
		if (str[j] == c)
			return (&str[j]);
		i--;
		j--;
	}
	return (NULL);
}
/* //i = ft_strlen(str) - 1; Need start check 
   from last char \0 thus no need -1 */
/*int main(void)
{
	const char str1[] = "hello world!";
	char c1 = '!';
	char *occur1 = ft_strrchr(str1, c1);
	printf("ft_strchr %s \n", occur1);
	const char str2[] = "hello world!";
	char c2 = '!';
	char *occur2 = strrchr(str2, c2);
	printf("___strchr %s \n", occur2);
	const char str3[] = "hello world!";
	char c3 = 'z';
	char *occur3 = ft_strrchr(str3, c3);
	printf("ft_strchr %s \n", occur3);
	const char str4[] = "hello world!";
	char c4 = 'z';
	char *occur4 = strrchr(str4, c4);
	printf("___strchr %s \n", occur4);
}*/
