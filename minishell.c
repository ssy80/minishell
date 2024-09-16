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

/* dir is the cwd + :  eq the prompt to print*/
void	getprompt(char *dir)
{
	int	i;

	ft_bzero(dir, sizeof(char) * MAXLEN);
	getcwd(dir, sizeof(char) * MAXLEN);
	i = ft_strlen(dir);
//printf("%d\n", i);
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
	printf("input: %s\n", input);
	if (!input)
		return (freenull(input), -1);
	len = ft_strlen(input);
	if (len > size - 1)
		return (freenull(input), ft_putstr_fd("str too long\n", 1), -1);
	exitcommand(input, data);
	ft_strlcpy(buf, input, len + 1);
	add_history(buf);
	return (freenull(input), 0);
}

int	main(int ac, char *av[], char **envp)
{
	char	buf[MAXLEN];
	char	dir[MAXLEN];
	t_data	data;
	t_cmd	*tree;
	
//	t_list *token_list;

// Print environment variables
/*for (int i = 0; envp[i] != NULL; i++) {
	printf("Environment variable %d: %s\n", i, envp[i]);
}*/

	(void)av;
	(void)ac;
	initfd(dir);
	initdata(buf, envp, &data);
	server();
	while (getcmd(buf, MAXLEN, dir, &data) >= 0)
	{
		if(ft_strlen(buf) == 0)//empty input
			continue ;
		gettkn(&data, 0, 0);
		loadcmdtkn(&data);
		printf("buffer: %s\n", data.buf);
		for (int i =0; i<data.itr;i++)
			printf("%s\n", data.cmd[i]);
		if (syn_check(&data))
			write(1, "true\n", 5);
		else
			write(1, "false\n", 6);
		// tree = parsepipe(&data, 0);
		(void) tree;
//		token_list = process_raw_input(buf);
//		parse_token_list(&token_list);
//		printf("----\n");
//		print_token_list(token_list);
//		execute_list(token_list);
		//if (builtin_func(buf, &data) == 0)
		//	continue ;
		freedatacmd(&data);
	}
	exitcl(0);
}
