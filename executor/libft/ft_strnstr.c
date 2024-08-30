/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:08:07 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 18:38:58 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	check_str(const char *haystack, const char *needle, size_t i)
{
	size_t	j;
	size_t	len_needle;

	len_needle = ft_strlen(needle);
	if (haystack[i] == needle[0])
	{
		j = 0;
		while (j < len_needle)
		{
			if (needle[j] != haystack[i])
				break ;
			j++;
			i++;
		}
		if (j == len_needle)
			return (i - len_needle);
	}
	return (-1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	size_t	len_haystack;
	size_t	len_needle;

	len_haystack = ft_strlen(haystack);
	len_needle = ft_strlen(needle);
	i = 0;
	if (len_needle > len_haystack)
		return (NULL);
	else if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && ((i + len_needle) <= len))
	{
		j = check_str(haystack, needle, i);
		if (j > -1)
			return (&((char *)haystack)[j]);
		i++;
	}
	return (NULL);
}
/*int main(void)
{
	char s1[] = "hello wordld!";
	char find1[] = "wordl";
	char *d1 = ft_strstr(s1, find1);
	printf("ft_strstr %s \n", d1);
	char *d2 = strstr(s1, find1);
	printf("___strstr %s \n", d2);
	
	char *d3 = ft_strnstr(s1, find1, 14);
	printf("ft_strnstr %s \n", d3);
	char *d4 = ft_strnstr(s1, find1, 11);
	printf("ft_strnstr %s \n", d4);
}*/
