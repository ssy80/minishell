/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 22:51:06 by ssian             #+#    #+#             */
/*   Updated: 2024/10/14 15:43:59 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

/* ls: /usr/bin + / + ls */
static char	*form_filepath(char *split_path, char *cmd)
{
	char	*command;
	char	*copy_command;

	command = NULL;
	copy_command = NULL;
	command = ft_strjoin(split_path, "/");
	if (command == NULL)
		return (NULL);
	copy_command = ft_strdup(command);
	if (copy_command == NULL)
		return (free(command), NULL);
	free(command);
	command = ft_strjoin(copy_command, cmd);
	if (command == NULL)
		return (free(copy_command), NULL);
	free(copy_command);
	return (command);
}

static char	*get_filepath(char *env_path, char *cmd)
{
	int		i;
	char	**split_path;
	char	*command;

	command = NULL;
	split_path = ft_split(env_path, ':');
	i = 0;
	while (split_path[i])
	{
		free(command);
		command = form_filepath(split_path[i], cmd);
		if (command == NULL)
			return (free_charchar_str(split_path), NULL);
		if (access(command, F_OK) == 0)
			return (free_charchar_str(split_path), command);
		i++;
	}
	return (free_charchar_str(split_path), free(command), NULL);
}

static char	*get_command_path(char *cmd, t_data *data)
{
	char	*command;
	char	*env_path;

	if (is_cmd_path(cmd) == 1)
	{
		command = ft_strdup(cmd);
		if (command == NULL)
			return (NULL);
		return (command);
	}
	env_path = get_env_path(data);
	command = get_filepath(env_path, cmd);
	return (command);
}

static void	check_dir(t_cmd *cmd, t_data *data)
{
	if (ft_strchr(cmd->cmd, '/') != NULL)
	{
		if (is_dir(cmd->cmd) == 1)
			error_command_is_dir(cmd, data);
	}
}

void	do_command(t_cmd *cmd, t_data *data)
{
	char	*command;
	char	**envp;

	check_dir(cmd, data);
	command = get_command_path(cmd->cmd, data);
	if (ft_strlen(get_env_path(data)) == 0 && command == NULL)
		error_no_file(cmd, data);
	else if (command == NULL)
		error_no_command(cmd, data);
	else
	{
		if (check_got_file(command) == 0)
			error_no_file(cmd, data);
		else if (check_x_permission(command) == 0)
			error_no_permission(cmd, data);
		envp = get_current_env(data);
		if (envp == NULL)
			error_no_env(cmd, data);
		if (execve(command, cmd->args, envp) == -1)
		{
			free(envp);
			free(command);
			error_execve(cmd, data);
		}
	}
}
