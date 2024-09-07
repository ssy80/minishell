/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:30:35 by yoong             #+#    #+#             */
/*   Updated: 2024/08/27 13:30:37 by yoong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*execcmd(t_data *data)
{
	t_execcmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_execcmd));
	if (!cmd)
		return (freenullall(data), exitcl(1), NULL);
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*pipecmd(t_data *data, t_cmd *left, t_cmd *right)
{
	t_pipecmd *cmd;

	cmd = ft_calloc(1, sizeof(t_pipecmd));
	if (!cmd)
		return (freenullall(data), exitcl(1), NULL);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*redircmd(t_cmd *subcmd, char *str, int mode, int fd)
{
	t_redircmd *cmd;

	cmd = ft_calloc(1, sizeof(t_redircmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = str;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}


int	parsetype(char *tkn)
{
	int l;

	if (!tkn)
		return (ERRSYM);
	l = ft_strlen(tkn);
	if (!is_sym(tkn[0]))
		return (CHARSYM);
	if (l == 1 && tkn[0] == '<')
		return (LSYM);
	if (l == 1 && tkn[0] == '>')
		return (MSYM);
	if (l == 2 && tkn[0] == '>' && tkn[1] == '>')
		return (MMSYM);
	if (l == 2 && tkn[0] == '<' && tkn[1] == '<')
		return (LLSYM);
	if (l == 1 && tkn[0] == '|')
		return (PIPESYM);
	return (ERRSYM);
}


t_cmd	*parseredir(t_cmd *cmd, t_data *data, int i)
{
	int	type;

	type = parsetype(data->cmd[i]);
	// if (!(type == LSYM || type == MSYM ||type == MMSYM ||type == LLSYM))
	// 	return (freenullall(data), exitcl(1), NULL);
	while (type == LSYM || type == MSYM ||type == MMSYM ||type == LLSYM)
	{
		if (!data->cmd[i+1] || parsetype(data->cmd[i+1]) != CHARSYM)
			return (freenullall(data), exitcl(1), NULL);
		if (type == LSYM)
			cmd = redircmd(cmd, data->cmd[i+1], O_RDONLY, 0);
		else if (type == MSYM)
			cmd = redircmd(cmd, data->cmd[i+1],  O_WRONLY|O_CREAT|O_TRUNC, 1);
		else if (type == MMSYM)
			cmd = redircmd(cmd, data->cmd[i+1], O_WRONLY|O_CREAT, 1);
		else if (type == LLSYM)
			cmd = redircmd(cmd, data->cmd[i+1], O_WRONLY|O_TRUNC, 1);
		i += 2;
		type = parsetype(data->cmd[i]);
	}
	return cmd;
}

t_cmd	*parseexec(t_data *data, int i)
{
	t_cmd		*ret;
	t_execcmd	*cmd;
	int			argc;

	ret = execcmd(data);
	cmd = (t_execcmd *)ret;
	argc = 0;
	ret = parseredir(ret, data, data->tkn_no);
	i = data->tkn_no;
	while (data->cmd[i] && parsetype(data->cmd[i]) >= CHARSYM)
	{
		if (parsetype(data->cmd[i]) != CHARSYM)
			return (freenullall(data), exitcl(1), NULL);
		cmd->argv[argc] = data->cmd[i];
		cmd->eargv[argc] = data->cmd[i];
		argc++;
		i++;
		data->tkn_no = i;
		if (argc >= MAXARGS)
			return (freenullall(data), exitcl(1), NULL);
		ret = parseredir(ret, data, data->tkn_no);
	}
	return (ret);
}

t_cmd	*parsepipe(t_data *data, int i)
{
	t_cmd	*cmd;

	cmd = parseexec(data, i);
	if (data->cmd[data->tkn_no] && data->cmd[data->tkn_no][0] == '|' && data->cmd[data->tkn_no][1] == '\0')
	{
		data->tkn_no++;
		cmd = pipecmd(data, cmd, parsepipe(data, data->tkn_no));
	}
	return cmd;
}

