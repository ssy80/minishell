/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:11:33 by ssian             #+#    #+#             */
/*   Updated: 2024/05/22 16:48:03 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	checkset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	int		start;
	int		end;
	int		len;

	i = 0;
	while (checkset(s1[i], set) == 1)
		i++;
	if (i == 0)
		start = 0;
	else
		start = i;
	i = ft_strlen(s1) - 1;
	while (checkset(s1[i], set) == 1)
		i--;
	end = i;
	len = (end - start) + 1;
	str = ft_substr(s1, start, len);
	return (str);
}
/*int main(void)
{
	char s1[] = "xx  \n\t\n\v\f\r abbba123\n456x\t\n     xx";
	char set[]= " a1b\t\n\v\f\r";

	char *str = ft_strtrim(s1, set);
	printf("%s\n", str);
	printf("%s\n", "xx  \n\t\n\v\f\r abbba123\n456x\t\n     xx");
	free(str);
}*/
