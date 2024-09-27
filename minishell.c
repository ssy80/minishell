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
	{
		printf("--need free data struct before exit--\n");
		return (free_all(data), -1);
		//return (freenull(input), free_all(data), -1);
	}
	len = ft_strlen(input);
	if (len > size - 1)
		return (freenull(input), ft_putstr_fd("str too long\n", 1), -1);

//	exitcommand(input, data);

	if (is_spaces(input) == 0)
	{
		ft_strlcpy(buf, input, len + 1);
		add_history(buf);
	}

	return (freenull(input), 0);
}

int	main(int ac, char *av[], char **envp)
{
	char	buf[MAXLEN];
	char	dir[MAXLEN];
	t_data	data;
	t_list	*cmd_list;

	(void)av;
	(void)ac;
	initfd(dir);
	initdata(buf, envp, &data);
	server();
	while (getcmd(buf, MAXLEN, dir, &data) >= 0)
	{

		if(ft_strlen(buf) == 0)         //empty input or is spaces
			continue ;

		gettkn(&data, 0, 0);
		loadcmdtkn(&data);

		//printf("buffer: %s\n", data.buf);
		//for (int i =0; i<data.itr;i++)
		//	printf("%s\n", data.cmd[i]);
		
		if (!syn_check(&data))
		{
			free_datacmd(&data);
			continue;
		}
			
		/*if (syn_check(&data))
			write(1, "syntax checker: true\n", 21);
		else
			write(1, "syntax checker:false\n", 21);*/

		//printf("\nThis is expander\n");
		for (int i =0; i<data.itr;i++)
		{
			if (expander(data.cmd[i], &data, i) == 0)
			{
				free_datacmd(&data);
				freenullall(&data);
				exit(EXIT_FAILURE);
			}
		}

		//cmd_list = NULL;
		cmd_list = create_cmd_list(&data);
		if (cmd_list == NULL)                    //malloc failed ?
		{
			free_datacmd(&data);
			freenullall(&data);
			//ft_putstr_fd("cmd_list: ", STDERR_FILENO);
            //ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
			//break;
			exit(EXIT_FAILURE);
		}

		data.cmd_list = cmd_list;

//print_cmd(cmd_list);

		if (process_cmd_list(cmd_list, &data) == 0)
		{
			free_cmdlist(cmd_list);
			ft_freelist(cmd_list);
			free_datacmd(&data);
			exit(EXIT_FAILURE);
		}
	
		free_cmdlist(cmd_list);
		ft_freelist(cmd_list);
		free_datacmd(&data);

	}
	exitcl(0);
}
