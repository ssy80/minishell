/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:04:01 by ssian             #+#    #+#             */
/*   Updated: 2024/09/24 15:04:04 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int get_matched_idx(char *str, char c)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (-1);
}

static int starts_with(char *str, char *start)
{
    int i;

    i = 0;
    while (start[i] && str[i])
    {
        if (start[i] != str[i])
        {
            return (0);
        }
        i++;
    }
    return (1);
}

/*check is AA= is already in env list, if yes, replace witht the new var*/
int replace_var_in_env(char *str, t_data *data)
{
    char *start;
    t_list *env_list;
    char *env_var;
    int idx;
    char *tmp;

    start = NULL;
    idx = get_matched_idx(str, '=');
    start = ft_substr(str, 0, (idx + 1));                // get A=
    if (start == NULL)
        return (0);

printf("start: %s\n", start);
printf("str: %s\n", str);

	env_list = data->env;

	while (env_list != NULL)
	{
        env_var = (char *)env_list->content;
		if (starts_with(env_var, start) == 1)             //yes already have var, do replaced it
        {
            free(env_var);
            env_var = NULL;
            free(start);                                   //need free prev str in env_list[i]??
            tmp = ft_strdup(str);
            env_list->content = tmp;
            return (1);
        }
		env_list = env_list->next;
	}
    free(start); 
    return (0);
}

int is_var_in_env(char *str, t_data *data)
{
    char    *start;
    t_list  *env_list;
    char    *env_var;
    int     idx;

    idx = get_matched_idx(str, '=');
    start = ft_substr(str, 0, (idx + 1));                // get A=, malloc failed ?
    if (start == NULL)
    {
        return (0);
    }
	env_list = data->env;
	while (env_list != NULL)
	{
        env_var = (char *)env_list->content;
		if (starts_with(env_var, start) == 1)           //yes ahave
            return (free(start), 1);
		env_list = env_list->next;
	}
    return (free(start), 0);
}

int remove_var_in_env(char *start, t_data *data)
{
    t_list  *env_list;
    char    *env_var;
    t_list  *new_list;
    t_list  *envnode;

    new_list = NULL;
    env_list = data->env;
	while (env_list != NULL)
	{
        env_var = (char *)env_list->content;
		if (starts_with(env_var, start) == 0)                         
        {
            env_var = ft_strdup(env_var);                                  //reuse var env_var
            if (env_var == NULL)
                return(ft_lstclear(&new_list, free), 0);
            envnode = ft_lstnew(env_var);                                  //malloc failed?
            if (envnode == NULL)
                return (free(env_var), ft_lstclear(&new_list, free), 0);
            ft_lstadd_back(&new_list, envnode);
        }
		env_list = env_list->next;
	}
    env_list = data->env;
    data->env = new_list;
    ft_lstclear(&env_list, free);
    return (1);
}

