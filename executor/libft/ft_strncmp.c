/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:06:23 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 15:38:33 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((i < n - 1) && (str1[i] != '\0') && (str2[i] != '\0'))
	{
		if (str1[i] != str2[i])
			break ;
		i++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
/**(i < n - 1) - somehow it needs n -1 to work??? 
needs return unsigned char as well **/
/*int	main(void)
{
	char str1[] = "gello";
	char str2[] = "he";
	printf("ft_strncmp %d \n", ft_strncmp(str1, str2, 5));
	printf("___strncmp %d \n", strncmp(str1, str2, 5));
}*/
