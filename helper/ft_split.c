/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:34:31 by yoong             #+#    #+#             */
/*   Updated: 2024/04/15 05:18:57 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_empty_str(char const *str, int i, int j)
{
	int	end;

	end = i + j -1;
	while (i <= end)
	{
		if (!(str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
			return (0);
		i++;
	}
	return (1);
}

char	**array(t_list **head)
{
	t_list	*cp;
	t_list	*np;
	int		i;
	char	**ans;

	cp = *head;
	i = 0;
	while (cp && ++i >= 0)
		cp = cp->next;
	ans = malloc((i + 1) * sizeof(char *));
	if (!ans)
		return (ft_lstclear(head, free), NULL);
	ans[i] = 0;
	i = 0;
	cp = *head;
	while (cp)
	{
		ans[i] = cp->content;
		np = cp->next;
		free(cp);
		cp = np;
		i++;
	}
	return (ans);
}

void	create_ll(int i, int j, char const *s, t_list **head)
{
	char	*a;
	t_list	*res;
	int		tmp;

	if (is_empty_str(s, i, j))
		return ;
	a = malloc((j - i + 1) * sizeof(char));
	if (!a)
		return (ft_lstclear(head, free));
	res = ft_lstnew(a);
	if (!res)
		return (ft_lstclear(head, free), free(a));
	a[j - i] = '\0';
	tmp = i;
	while (s[i] && i < j)
	{
		a[i - tmp] = s[i];
		i++;
	}
	res->content = a;
	ft_lstadd_back(head, res);
}

char	**ft_split(char const *s, char c)
{
	t_list	*list;
	int		i;
	int		j;

	i = 0;
	list = NULL;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		create_ll(i, i + j, s, &list);
		if (!list)
			return (NULL);
		if (j == 0)
			i++;
		else
			i += j;
	}
	return (array(&list));
}

// int	main(void)
// {
// char a[] = "  \n0: zero\n1: one\n2: two\n3: three\n  ";
// 	char a[] = "      split       this for   me  !       ";
// 	char c = ' ';
// 	char **array;

// 	array = ft_split(a, c);
// 	int i = -1;
// 	while (array[++i] != 0)
// 		printf("%s\n",array[i]);
// 	i = -1;
// 	while (array[++i])
// 		free(array[i]);
// 	free(array);
// }
