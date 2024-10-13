/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_q_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:17:40 by yoong             #+#    #+#             */
/*   Updated: 2024/10/10 16:17:42 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// s should be ' or "
int	pq(char *str, int i, t_stack *stack, char s)
{
	if (!str[i])
		return (i);
	if (str[i] == s)
		return (i + 1);
	stack->line[stack->tail++] = str[i];
	return (pq(str, i + 1, stack, s));
}

// walk the s and perform quote removal
void	ps(char *s, t_stack *stack, int i)
{
	if (!s[i])
		return ;
	if (s[i] == '\'')
		return (ps(s, stack, pq(s, i + 1, stack, '\'')));
	if (s[i] == '"')
		return (ps(s, stack, pq(s, i + 1, stack, '"')));
	stack->line[stack->tail++] = s[i];
	return (ps(s, stack, i + 1));
}

// func to be used for quote removal
void	qremoval(char *s, t_stack *stack)
{
	ft_bzero(stack, sizeof(t_stack));
	ps(s, stack, 0);
}
