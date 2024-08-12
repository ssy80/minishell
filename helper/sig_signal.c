/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:53:46 by yoong             #+#    #+#             */
/*   Updated: 2024/08/02 19:54:19 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
ctrl-\  SIGQUIT = does nothing
ctrl-c  SIGINT = display new prompt on new line
ctrl-d  EOF = exit shell
*/
void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void) context;
	(void) info;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ign_sigquit(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

// module for handle ctrlC, ctrlD and ctrl
void	server(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	ign_sigquit();
	ft_bzero(&sa, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_handler = NULL;
	sa.sa_sigaction = handle_signal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (ft_putstr_fd("Error adding SIGINT\n", 1), exit(1));
}
