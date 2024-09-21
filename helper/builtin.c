/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:35:52 by ssian             #+#    #+#             */
/*   Updated: 2024/09/18 13:35:55 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin_fn(char *cmd)
{
    if (equals(cmd, "echo") == 1)
        return (1);
    if (equals(cmd, "cd") == 1)
        return (1);
    if (equals(cmd, "pwd") == 1)
        return (1);
    if (equals(cmd, "export") == 1)
        return (1);
    if (equals(cmd, "unset") == 1)
        return (1);
    if (equals(cmd, "env") == 1)
        return (1);
    if (equals(cmd, "exit") == 1)
        return (1);
    return (0);
}

void builtin_get_env(t_data *data)
{
   getmyenv(data);
}

/*static char *remove_quote(char *str)
{
    int i;
    int len;
    char *sub_str;

    len = ft_strlen(str);

    i = 0;

    sub_str = ft_substr(str, i+1, len-2);
    return (sub_str);
}*/

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


int starts_with(char *str, char *start)
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
		if (starts_with(env_var, start) == 1)           //yes already have var, do replaced it
            return (free(start), 1);
		env_list = env_list->next;
	}
    return (free(start), 0);
}

/*if starts with a= already in list, replace with new a=... 
  if not in list then add args[i] to it.
  if invalid format "export a"? - will be ignored no error msg. 
  if invalid format "=" or "=aaa"? will have error msg.
*/
int builtin_export(char **args, t_data *data)
{
    int i;

    i = 1;
    while (args[i])
    {
        if (ft_strchr(args[i], '=') == NULL)                          //ignored arg without '='
        {
            i++;
            continue ;
        }
        if (args[i][0] == '=')                                        //[0] first char '=' is invalid format 
        {
            ft_putstr_fd("export: ", STDERR_FILENO);
            ft_putstr_fd("'", STDERR_FILENO);
            ft_putstr_fd(args[i], STDERR_FILENO);
            ft_putstr_fd("'", STDERR_FILENO);
            ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
            i++;
            continue ;
        }
        if (is_var_in_env(args[i], data) == 1)                        //replace tmp later
        {
            if (replace_var_in_env(args[i], data) == 0)               //error malloc??
                return (0);                        
        }
        else                                                         //add new env var to list
        {
            if (addenvvar(args[i], data) == -1)
                return (0);
        }
        i++;
    }
    return (1);
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

/*look for the arg AA=aaa - AA in the env list, remove it if have*/
int builtin_unset(char **args, t_data *data)
{
    char *tmp;
    int i;

    i = 1;                                                  //start from [1], [0] is command 
    while (args[i])
    {
        tmp = ft_strjoin(args[i], "=");                     // AA=
        if (is_var_in_env(tmp, data) == 1)                  // got AA=               
        {
            if (remove_var_in_env(tmp, data) == 0)
                return (free(tmp), 0);
        }
        free(tmp);
        i++;
    }
    return (1);
}

void builtin_exit(t_data *data)
{
    freenullall(data);
    exit(0);
}