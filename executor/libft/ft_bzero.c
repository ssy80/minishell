/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:23:13 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 19:28:40 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *str_, size_t n)
{
	size_t	i;
	char	*str;

	str = (char *)str_;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
/*int	main(void)
{
	char str1[]="hello world!";
	ft_bzero(&str1, 2);
	printf("ft_bzero %s \n", str1);
	char str2[]="hello world!";
	bzero(&str2, 2);
	printf("bzero %s \n", str2);
}*/
