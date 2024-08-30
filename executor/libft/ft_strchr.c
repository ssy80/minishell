/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:52:24 by ssian             #+#    #+#             */
/*   Updated: 2024/05/23 14:30:13 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str_, int c)
{
	size_t	i;
	size_t	len;
	char	*str;

	str = (char *)str_;
	len = ft_strlen(str_);
	if (c >= 256)
		c = c % 256;
	i = 0;
	while (i <= len)
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
/* while (i <= ft_strlen(str)) - check to include \0 */
/*int main(void)
{
	const char str1[] = "hello world!";
	char c1 = 'w';
	char *occur1 = ft_strchr(str1, c1);
	printf("ft_strchr %s \n", occur1);
	const char str2[] = "hello world!";
	char c2 = 'w';
	char *occur2 = strchr(str2, c2);
	printf("___strchr %s \n", occur2);
	const char str3[] = "hello world!";
	char c3 = 'z';
	char *occur3 = ft_strchr(str3, c3);
	printf("ft_strchr %s \n", occur3);
	const char str4[] = "hello world!";
	char c4 = 'z';
	char *occur4 = strchr(str4, c4);
	printf("___strchr %s \n", occur4);

	//const char str5[] = "there is so 
	\0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
	const char str5[] = "";
	//char c5 = 'a';
	char *occur5 = ft_strchr(str5, 't' + 256);
	printf("ft_strchr %s\n", occur5);
	
	char *occur6 = strchr(str5, 't' + 256);
	printf("___strchr %s\n", occur6);

	printf("t+256: %c", 't'+256);
	printf("256: %c", 256);
}*/
