/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:51:35 by ssian	           #+#    #+#             */
/*   Updated: 2024/05/23 19:47:13 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static char	*join(char *str_, char const *s, size_t *i, size_t len)
{
	int		j;
	char	*str;

	str = str_;
	j = 0;
	while ((*i < len) && (s[j] != '\0'))
	{
		str[*i] = s[j];
		*i = *i + 1;
		j++;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	str = join(str, s1, &i, len);
	str = join(str, s2, &i, len);
	str[i] = '\0';
	return (str);
}
/*int	main(void)
{
	char *s1 = "42";
	char *s2 = "SG";
	char *str = ft_strjoin(s1, s2);
	printf("%s", str);
}*/
