/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:17:52 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 12:22:49 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1024);
	}
	return (0);
}
/*int main(void)
{
	printf("ft_isalpha: %d \n", ft_isalpha('s'));
	printf("isalpha: %d \n", isalpha('s'));
	printf("ft_isalpha: %d \n", ft_isalpha(1));
	printf("isalpha: %d \n", isalpha(1));
	printf("ft_isalpha: %d \n", ft_isalpha('Z'));
	printf("isalpha: %d \n", isalpha('Z'));
}*/
