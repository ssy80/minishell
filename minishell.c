/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:41:38 by yoong             #+#    #+#             */
/*   Updated: 2024/10/16 15:03:01 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	create_and_process(t_data *data)
{
	t_list	*cmd_list;

	cmd_list = create_cmd_list(data);
	if (cmd_list == NULL)
		error_main(data);
	data->cmd_list = cmd_list;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_signal_in_command();
	if (process_cmd_list(cmd_list, data) == 0)
	{
		free_all(data);
		exit(EXIT_FAILURE);
	}
	free_main_last(cmd_list, data);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	server();
}

static void	initalization(char *dir, char *buf, char **envp, t_data *data)
{
	initfd(dir);
	initdata(buf, envp, data);
	server();
	set_sigint_status(data);
	update_exit_status(0, data);
}

bool	syntaxfail(t_data *data)
{
	update_exit_status(2, data);
	ft_putstr_fd("syntax error\n", STDERR_FILENO);
	free_datacmd(data);
	return (true);
}

// initfd(dir);
// initdata(buf, envp, &data);
// server();
// set_sigint_status(&data);
// update_exit_status(0, &data);
int	main(int ac, char *av[], char **envp)
{
	char	buf[MAXLEN];
	char	dir[MAXLEN];
	t_data	data;

	(void)av;
	(void)ac;
	initalization(dir, buf, envp, &data);
	cmdline(ac, av, envp, &data);
	while (getcmd(buf, MAXLEN, dir, &data) >= 0)
	{
		if (ft_strlen(buf) == 0)
			continue ;
		gettkn(&data, 0, 0);
		loadcmdtkn(&data);
		if (!syn_check(&data) && syntaxfail(&data))
			continue ;
		if (do_expander(&data) == 0)
			error_main(&data);
		retokenise(&data);
		if (!data.cmd[0])
			continue ;
		create_and_process(&data);
	}
	exitcl(0);
}
