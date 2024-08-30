/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:02:37 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 12:20:40 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*checks for an alphanumeric character; 
it is equivalent to (isalpha(c) || isdigit(c)).*/
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) > 0 || ft_isdigit(c) > 0)
	{
		return (8);
	}
	return (0);
}
/*int	main(void)
{
	printf("ft_isalum %d \n", ft_isalnum('9'));
	printf("isalum %d \n", isalnum('9'));
	printf("ft_isalum %d \n", ft_isalnum('0'));
	printf("isalum %d \n", isalnum('0'));
	printf("ft_isalum %d \n", ft_isalnum('a'));
	printf("isalum %d \n", isalnum('a'));
}*/
