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

void set_sigint_status(t_data *data)
{
    static t_data *tmp_data;// = NULL;
  
    if (data == NULL)
    {
        if (tmp_data != NULL) 
			update_exit_status(130, tmp_data);
			//tmp_data = NULL;
    } 
    else 
        tmp_data = data;
}


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
	//	g_var = 130;
		set_sigint_status(NULL);
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

/*handle control D and Control C when executing cmdlist */
void handle_signal_in_command(int sig)
{
	//printf("sig: %d\n", sig);
	printf("\n");
	(void)sig;
}

void set_signal_in_command()
{
	signal(SIGINT, handle_signal_in_command);
	signal(SIGQUIT, handle_signal_in_command);
}