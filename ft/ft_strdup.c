/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:38:57 by ssian             #+#    #+#             */
/*   Updated: 2024/05/23 19:46:05 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup_str;
	size_t	i;

	len = ft_strlen(s);
	dup_str = (char *)malloc(sizeof(char) * (len + 1));
	if (dup_str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup_str[i] = s[i];
		i++;
	}
	dup_str[i] = '\0';
	return (dup_str);
}
/*int	main(void)
{
	char str[] = "hello";
	char *dup1;
	dup1 = ft_strdup(str);
	printf("ft_strdup %s \n", dup1);
	free(dup1);
	char *dup2 = strdup(str);
	printf("___strdup %s \n", dup2);
	free(dup2);
}*/
