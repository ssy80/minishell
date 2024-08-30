/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:20:14 by ssian             #+#    #+#             */
/*   Updated: 2024/05/23 14:24:38 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;
	char	*str;	

	if ((long)nmemb < 0 && (long)size < 0)
		return (NULL);
	else if ((long)nmemb < 0 && (long)size > 0)
		return (NULL);
	else if ((long)nmemb > 0 && (long)size < 0)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	str = (char *)ptr;
	i = 0;
	while (i < (nmemb * size))
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
/*int	main(void)
{
	char *str = (char *)ft_calloc(5, sizeof(char));
	int j = 0;
	while (str[j] == '\0')
	{
		printf("ft_calloc %d \n", j);
		j++;
	}
	free(str);
	char *str2 = (char *)calloc(5, sizeof(char));
	puts(str2);
	int i = 0;
	while (str2[i] == '\0')
	{
		printf("___calloc %d \n", i);
		i++;
	}
	free(str2);
	int *str3 = (int *)ft_calloc(5, sizeof(int));
	int k = 0;
	while (str3[k] == '\0')
    {
		printf("ft_calloc %d \n", k);
		k++;
    }
	free(str3);
	int *str4 = (int *)calloc(5, sizeof(int));
    int l = 0;
    while (str4[l] == '\0')
	{
		printf("___calloc %d \n", l);
		l++;
    }
	free(str4);
}*/
