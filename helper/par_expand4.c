/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_expand4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:34:31 by yoong             #+#    #+#             */
/*   Updated: 2024/10/12 17:34:35 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// if ((i == 0 || s[i - 1] == ' ') && (s[i] == '|' || s[i] == '<' || 
// s[i] == '>') && (!s[i + 1] || s[i + 1] == ' '))
bool	isspecialchar1(char *s, int i)
{
	if (s[i] == '|' || s[i] == '<' || s[i] == '>')
		return (true);
	return (false);
}

// if ((i == 0 || s[i - 1] == ' ') && ((s[i] == '<' && s[i + 1] == '<') || 
// (s[i] == '>' && s[i + 1] == '>')) && 
// (!s[i + 1] || !s[i + 2] || s[i + 2] == ' '))
bool	isspecialchar2(char *s, int i)
{
	if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i + 1] == '>'))
		return (true);
	return (false);
}

void	insertqstack(char s, t_stack *stack, int no)
{
	int	i;

	i = -1;
	stack->line[stack->tail++] = '"';
	while (++i < no)
		stack->line[stack->tail++] = s;
	stack->line[stack->tail++] = '"';
}

void	expandswrapper(char *s, t_stack *stack)
{
	int	l;
	int	i;

	ft_bzero(stack, sizeof(t_stack));
	l = ft_strlen(s);
	i = -1;
	if (s[0] == '"' || s[0] == '\'')
		i = 1;
	if (s[l - 1] == '"' || s[l - 1] == '\'')
		l--;
	while (++i < l)
	{
		if (isspecialchar2(s, i))
		{
			insertqstack(s[i], stack, 2);
			i++;
		}
		else if (isspecialchar1(s, i))
			insertqstack(s[i], stack, 1);
		else
			stack->line[stack->tail++] = s[i];
	}
}
