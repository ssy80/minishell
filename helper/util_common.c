/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:59:27 by ssian             #+#    #+#             */
/*   Updated: 2024/10/16 14:08:35 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	equals(char *s1, char *s2)
{
	int	i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_dir(char *command)
{
	struct stat	sbuf;

	if (stat(command, &sbuf) != 0)
		return (0);
	return (S_ISDIR(sbuf.st_mode));
}

int	get_args_len(char **args)
{
	int	i;

	if (args == NULL)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_contain_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

int	cmdline(int argc, char **argv, char **envp, t_data *data)
{
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		ft_bzero(data, sizeof(t_data));
		copyenv(envp, data);
		server();
		set_sigint_status(data);
		update_exit_status(0, data);
		data->buf = argv[2];
		gettkn(data, 0, 0);
		loadcmdtkn(data);
		if (!syn_check(data) && syntaxfail(data))
			exitcl(0);
		if (do_expander(data) == 0)
			error_main(data);
		retokenise(data);
		if (!data->cmd[0])
			exitcl(0);
		create_and_process(data);
		exit(atoi(getenvvar("EXIT_STATUS", data)));
	}
	return (1);
}
