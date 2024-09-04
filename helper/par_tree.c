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

	cmd = ft_calloc(1, sizeof(t_execcmd *));
	if (!cmd)
		return (freenullall(data), exitcl(1), NULL);
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*pipecmd(t_data *data, t_cmd *left, t_cmd *right)
{
	t_pipecmd *cmd;

	cmd = ft_calloc(1, sizeof(t_pipecmd *));
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

	cmd = ft_calloc(1, sizeof(t_redircmd *));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = str;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd *)cmd);
}

// t_cmd	*parsecmd(t_data *data)
// {

// }

int	parsetype(char *tkn)
{
	int l;

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

// t_cmd	parseredir(t_data *data)
// {

// }