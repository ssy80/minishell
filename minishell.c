/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:41:38 by yoong             #+#    #+#             */
/*   Updated: 2024/08/02 17:41:41 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int g_var = 0;

/* dir is the cwd + :  eq the prompt to print*/
void	getprompt(char *dir)
{
	int	i;

	ft_bzero(dir, sizeof(char) * MAXLEN);
	getcwd(dir, sizeof(char) * MAXLEN);
	i = ft_strlen(dir);
	if (MAXLEN - 2 < i)
	{
		*dir = 0;
		return ;
	}
	dir[i] = ':';
	dir[i + 1] = ' ';
	dir[i + 2] = '\0';
}

// get input from user
int	getcmd(char *buf, int size, char *dir, t_data *data)
{
	char		*input;
	int			len;

	ft_bzero(buf, size);
	ft_bzero(data->tkn, MAXLEN * 2);
	ft_bzero(data->cmd, sizeof(char *) * MAXLEN);
	data->itr = 0;
	data->tkn_no = 0;
	getprompt(dir);
	if (!dir)
		return (ft_putstr_fd("dir too long to print\n", 1), -1);
	input = readline(dir);
	//printf("input: %s\n", input);
	if (!input)
		return (freenullall(data), -1);
	len = ft_strlen(input);
	if (len > size - 1)
	{
		ft_putstr_fd("str too long\n", 1);
		return (freenull(input), 0);
	}
		//return (freenull(input), freenullall(data), ft_putstr_fd("str too long\n", 1), -1);

	if (is_spaces(input) == 0)
	{
		ft_strlcpy(buf, input, len + 1);
		add_history(buf);
	}
	return (freenull(input), 0);
}

static int do_expander(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->itr)
	{
		if (expander(data->cmd[i], data, i) == 0)
			return (0);
		i++;
	}
	return (1);
}

static void error_main(t_data *data)
{
	free_datacmd(data);
	freenullall(data);
	exit(EXIT_FAILURE);
}

static void	free_main_last(t_list *cmd_list, t_data *data)
{
	free_cmdlist(cmd_list);
	ft_freelist(cmd_list);
	free_datacmd(data);
}

static void	create_and_process(t_data *data)
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

int	main(int ac, char *av[], char **envp)
{
	char	buf[MAXLEN];
	char	dir[MAXLEN];
	t_data	data;

	(void)av;
	(void)ac;
	initfd(dir);
	initdata(buf, envp, &data);
	server();
	set_sigint_status(&data);
	update_exit_status(0, &data);
	while (getcmd(buf, MAXLEN, dir, &data) >= 0)
	{
		if(ft_strlen(buf) == 0)
			continue ;	
		gettkn(&data, 0, 0);
		loadcmdtkn(&data);
		if (!syn_check(&data))
		{
			update_exit_status(2, &data);
			ft_putstr_fd("syntax error\n", STDERR_FILENO);
			free_datacmd(&data);
			continue;
		}
		if (do_expander(&data) == 0)
			error_main(&data);
		retokenise(&data);
		if (!data.cmd[0])
			continue ;
		create_and_process(&data);
	}
	exitcl(0);
}