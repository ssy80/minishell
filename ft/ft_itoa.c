/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:59:39 by ssian             #+#    #+#             */
/*   Updated: 2024/05/23 19:48:10 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	count_len(int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

/*len + 2 (add 1 null terminator and 1 '-' to the str[0])*/
static char	*do_sign_negative(size_t n, int len)
{
	char	*str;
	int		num;

	str = (char *)malloc((len + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	len++;
	str[len] = '\0';
	str[0] = '-';
	len--;
	while (n != 0)
	{
		num = n % 10;
		str[len] = num + 48;
		n = n / 10;
		len--;
	}
	return (str);
}

/*len + 1 (add 1 null terminator)*/
static char	*do_sign_positive(size_t n, int len)
{
	char	*str;
	int		num;

	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n == 0)
	{
		len--;
		str[len] = 48;
		return (str);
	}
	len--;
	while (n != 0)
	{
		num = n % 10;
		str[len] = num + 48;
		len--;
		n = n / 10;
	}
	return (str);
}

/*change int n_ to size_t n (if not INT_MIN * -1 will not work)*/
char	*ft_itoa(int n_)
{
	char	*str;
	int		len;
	int		sign;
	size_t	n;

	n = (size_t)n_;
	sign = 1;
	if ((int)n < 0)
	{
		sign = -1;
		n = n * -1;
	}
	if (n == -0)
		n = 0;
	len = count_len(n);
	if (sign == -1)
		str = do_sign_negative(n, len);
	else
		str = do_sign_positive(n, len);
	return (str);
}
/*int main(void)
{
//	int n = 156;
	int n = -1000;
//	int n = -0;
	//int n = INT_MIN; 
//	int n = INT_MAX;

	//n = n - (n % 10);
	//printf("%d \n", n);
	//n = n / 10;
	//printf("%d \n", n);
	//j = count_len(n);
	//printf("j %d\n", j);
	char *str = ft_itoa(n);
	printf("%s\n", str);
	printf("min int: %d\n", INT_MIN);
	printf("min int: %d\n", INT_MAX);
	free(str);
	//int a = 156;
	char *i2 = ft_itoa(n);
	//if (strcmp(i2, "156"))
	printf("%s\n", i2);
	printf("%d\n", strcmp(i2, "0"));
	printf("%s\n", i2);
	free(i2);
}*/
