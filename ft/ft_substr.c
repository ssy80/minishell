/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:05:30 by ssian             #+#    #+#             */
/*   Updated: 2024/05/23 19:47:43 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/*len = strlen(s) - start; so as not to 
	create unnecesary big unused m space */
char	*ft_substr(char const *s, unsigned int start_, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	start;

	if (s == NULL)
		return (NULL);
	start = (size_t)start_;
	if (start >= (ft_strlen(s)))
		len = 0;
	else if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len && (s[start] != '\0'))
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
/*if (start >= ft_strlen(s)) len = 0  -  set len to 0 
  if cannot substr, so that it will return a '\0' sub str*/
/*int	main(void)
{
	const char s[] = "0123456789";
	char *d = ft_substr(s, 8, 10);
	printf("%s \n", d);
	free(d);
}*/
