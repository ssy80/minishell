/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:04:39 by ssian             #+#    #+#             */
/*   Updated: 2024/05/24 13:52:16 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	check_delimiter(char s, char c)
{
	if (s == c)
		return (1);
	if (s == '\0')
		return (1);
	return (0);
}

static int	count_words(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if ((check_delimiter(str[i], c) == 0)
			&& (check_delimiter(str[i + 1], c) == 1))
			count++;
		i++;
	}
	return (count);
}

static char	**freeall(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
	return (str);
}

static char	**do_sub(char **str, char const *s, char c)
{
	int	i;
	int	k;
	int	start;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (check_delimiter(s[i], c) == 0)
		{
			start = i;
			while (check_delimiter(s[i], c) == 0)
				i++;
			str[k] = ft_substr(s, start, i - start);
			if (str[k] == NULL)
				return (freeall(str));
			k++;
		}
		else
			i++;
	}
	str[k] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		wordcount;

	wordcount = count_words((char *)s, c);
	str = (char **)malloc((wordcount + 1) * sizeof(char *));
	if (str == NULL)
		return (NULL);
	str = do_sub(str, s, c);
	return (str);
}
/*int	main(void)
{
	char str[] = "** ***tt***\n***hello**s*w*world***";
	char **s = ft_split(str, '*');
	int i = 0;
	while (s[i])
	{
		printf("%s\n", s[i]); 
		i++;
	}
	printf("%s", " \ntt\n\n\nhello\ns\nw\nworld\n"); 
	i = 0;
	while (s[i])
	{
         free(s[i]); 
         i++;
	}
	free(s);
}*/
