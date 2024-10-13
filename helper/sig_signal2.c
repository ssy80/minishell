/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_signal2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 04:54:42 by yoong             #+#    #+#             */
/*   Updated: 2024/10/13 04:54:44 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_signal_in_command(void)
{
	signal(SIGINT, handle_signal_in_command);
	signal(SIGQUIT, handle_signal_in_command);
}
