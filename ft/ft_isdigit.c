/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:48:20 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 12:24:43 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	return (0);
}
/*int	main(void)
{
	printf("ft_isdigit: %d \n", ft_isdigit('0'));
	printf("isdigit: %d \n", isdigit('0'));
	printf("ft_isdigit: %d \n", ft_isdigit('Z'));
	printf("isdigit: %d \n", isdigit('Z'));
}*/
