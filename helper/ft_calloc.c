/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 05:08:43 by yoong             #+#    #+#             */
/*   Updated: 2024/04/15 05:08:49 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*ans;

	ans = malloc(size * number);
	if (!ans)
		return (NULL);
	ft_bzero(ans, size * number);
	return (ans);
}
