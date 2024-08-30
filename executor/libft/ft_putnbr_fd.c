/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:13:07 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 13:11:48 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "libft.h"

/*temp[i++] - set temp[i] = 48 and increase i + 1, thus i = 1*/
void	ft_putnbr_fd(int n_, int fd)
{
	size_t	n;
	char	temp[11];
	int		i;
	int		num;

	n = (size_t)n_;
	if (n_ < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	i = 0;
	num = 0;
	if (n_ == 0)
		temp[i++] = 48;
	while (n != 0)
	{
		num = n % 10;
		temp[i] = num + 48;
		i++;
		n = n / 10;
	}
	while (i--)
		write(fd, &temp[i], 1);
}
/*int main(void)
{
	//int n = -123;
	//int n = INT_MIN;
	int	n = 100;
	ft_putnbr_fd(n, 1);
	//printf("%d\n", INT_MIN);
	//printf("%d\n", INT_MAX);
}*/
