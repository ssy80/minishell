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

char **get_current_env(t_data *data)
{
    char **env;
    t_list  *env_list;
    char    *env_var;
    int size;
    int i;

    env_list = data->env;
    size = ft_lstsize(env_list);
    env = malloc(sizeof(char *) * (size + 1));                 //malloc failed?
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
    env[i] = NULL;                                        //last = NULL

    return (env);
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
		if (starts_with(env_var, start) == 1)           //yes ahave
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

void builtin_exit()
{
    //freenullall(data);
    exit(0);
}

static char *get_pwd()
{
    char *path;

    path = malloc(sizeof(char) * MAXLEN);                 //malloc failed ??
    if (path == NULL)
        return (NULL);
    else
    {
        getcwd(path, sizeof(char) * MAXLEN);
        return (path);
    }
}


static int check_cd_args_len(char **args)
{
    int i;
    int count;

    i = 1;
    count = 0;
    while (args[i])
    {
        count++;
        i++;
    }
    return (count);
}

int builtin_cd(char **args, t_data *data)
{
    int count;
    char *new_pwd;
    char *new_path;

    count = check_cd_args_len(args);
    if (count == 0)                                                           //cd to HOME dir
    {
        if (is_var_in_env("HOME=", data) == 0)
        {
            ft_putstr_fd("cd: ", STDERR_FILENO);
            ft_putstr_fd("HOME not set\n", STDERR_FILENO);
        }
        else
        {
            if (chdir(getenvvar("HOME", data)) == 0)
            {
               
                new_pwd = ft_strjoin("PWD=", getenvvar("HOME", data));       //get "PWD=$HOME" //set pwd to HOME path
                if (new_pwd == NULL)
                        return (0);
                if (is_var_in_env(new_pwd, data) == 1)                        //replace tmp later
                {
                    if (replace_var_in_env(new_pwd, data) == 0)               //error malloc??
                        return (free(new_pwd), 0);                        
                }
                else                                                         //add new env var to list
                {
                    if (addenvvar(new_pwd, data) == -1)
                        return (free(new_pwd), 0);
                }
                free(new_pwd);
            }
            else
            {
                perror("cd");
            }
        }
    }
    else if (count == 1)                                                 //cd to args[1]
    {
        if (chdir(args[1]) == 0) 
        {
            new_path = get_pwd();
            if (new_path == NULL)
                return (0);
            new_pwd = ft_strjoin("PWD=", new_path);
            if (new_pwd == NULL)
                return (free(new_path), 0);
            free(new_path);
            if (is_var_in_env(new_pwd, data) == 1)                        //replace tmp later
            {
                if (replace_var_in_env(new_pwd, data) == 0)               //error malloc??
                    return (free(new_pwd), 0);                        
            }
            else                                                         //add new env var to list
            {
                if (addenvvar(new_pwd, data) == -1)
                    return (free(new_pwd), 0);
            }
            free(new_pwd);
        }
        else
        {
            perror("cd");
        }
    }
    else if (count > 1)                                                 //error too many arguments
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        ft_putstr_fd("too many arguments\n", STDERR_FILENO);
    }
    return (1);
}

void builtin_echo(char **args)
{
    int i;
    int flag_n;

    flag_n = 1;
    i = 1;
    if (equals(args[i], "-n") == 1)                           //0 = no \n at the end
    {
        flag_n = 0;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1] != NULL)
            ft_putstr_fd(" ", STDOUT_FILENO);
        i++;
    }
    if (flag_n == 1)                                       //1 = \n at the end
    {
        ft_putstr_fd("\n", STDOUT_FILENO);
    }
}
