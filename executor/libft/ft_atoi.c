/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:31:03 by ssian             #+#    #+#             */
/*   Updated: 2024/05/24 14:00:46 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		n;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - 48);
		i++;
	}
	return (n * sign);
}
/*int main(void)
{
	printf("ft_atoi %d \n", ft_atoi("		 -123abc"));
	printf("ft_atoi %d \n", ft_atoi("		 --123abc"));
	printf("ft_atoi %d \n", ft_atoi("        ++456abc"));
	printf("ft_atoi %d \n", ft_atoi("        789abc"));
	printf("ft_atoi %d \n", ft_atoi("        1000abc"));
	printf("ft_atoi %d \n", ft_atoi("        -abc123"));
	printf("ft_atoi %d \n", ft_atoi("        "));
	printf("ft_atoi %d \n", ft_atoi("        xyz	1234"));
	printf("___atoi %d \n", atoi("		 -123abc"));
	printf("___atoi %d \n", atoi("		 --123abc"));
	printf("___atoi %d \n", atoi("        ++456abc"));
	printf("___atoi %d \n", atoi("        789abc"));
	printf("___atoi %d \n", atoi("        1000abc"));
	printf("___atoi %d \n", atoi("        -abc123"));
	printf("___atoi %d \n", atoi("        "));
	printf("___atoi %d \n", atoi("        xyz	1234"));
}*/
