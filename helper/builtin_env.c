/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:12:51 by ssian             #+#    #+#             */
/*   Updated: 2024/09/22 16:12:53 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int builtin_get_env(char **args, t_data *data)
{
    if (get_args_len(args) > 1)
    {
        ft_putstr_fd("env: ", STDERR_FILENO);
        ft_putstr_fd("'", STDERR_FILENO);
        ft_putstr_fd(args[1], STDERR_FILENO);
        ft_putstr_fd("'", STDERR_FILENO);
        ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
        return (0);
    }
    else
        getmyenv(data);
    return (1);
}

char **get_current_env(t_data *data)
{
    char    **env;
    t_list  *env_list;
    char    *env_var;
    int     size;
    int     i;

    env_list = data->env;
    size = ft_lstsize(env_list);
    env = malloc(sizeof(char *) * (size + 1));
    if(env == NULL)
        return (NULL);
    i = 0;
	while (env_list != NULL)
	{
        env_var = (char *)env_list->content;
        env[i] = env_var;
        i++;
        env_list = env_list->next;
    }
    env[i] = NULL;
    return (env);
}

/*use EXIT_STATUS env var as storage*/
int update_exit_status(int status, t_data *data)
{
    char *str;
    char *value;

    value = ft_itoa(status);
    if (value == NULL)
        return (0);
    str = ft_strjoin("EXIT_STATUS=", value);
    if (str == NULL)
        return (free(value), 0); 
    if (is_var_in_env(str, data) == 1)
    {
        if (replace_var_in_env(str, data) == 0)
            return (free(str), free(value), 0);
    }
    else
    {
        if (addenvvar(str, data) == -1)
            return (free(str), free(value), 0);
    }
    free(str);
    free(value);
    return (1);
}