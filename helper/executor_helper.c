/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:36:24 by ssian             #+#    #+#             */
/*   Updated: 2024/08/28 16:36:26 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int equals(char *s1, char *s2)
{
    int i;

    if (s1 == NULL || s2 == NULL)
        return (0);
    i = 0;
    while(s1[i] || s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    return (1);
}

static void free_pipefd(int **pipefd, int i)
{
    int j;

    j = 0;
    while (j < i)
    {
        free(pipefd[j]);
        j++;
    }
    free(pipefd);
}

static void print_error_pipe()
{
    ft_putstr_fd("pipe: ", STDERR_FILENO);
    ft_putstr_fd("create pipe failed !\n", STDERR_FILENO);
}

static void print_error_pidt()
{
    ft_putstr_fd("pidt: ", STDERR_FILENO);
    ft_putstr_fd("create pidt failed !\n", STDERR_FILENO);
}

int **get_pipe(int size)
{
    int **pipefd;
    int i;

    pipefd = malloc(sizeof(int *) * size);                //malloc failed??
    if (pipefd == NULL)
        return (print_error_pipe(), NULL);

    ft_bzero(pipefd, sizeof(int *) * size);               

    i = 0;
    while (i < size)
    {
        pipefd[i] = malloc(sizeof(int) * 2);
        if (pipefd[i] == NULL)
        {
            free_pipefd(pipefd, i);
            return (print_error_pipe(), NULL);
        }
        ft_bzero(pipefd[i], sizeof(int) * 2);              //??
        i++;
    }
    return (pipefd);
}

pid_t *get_pidt(int size)
{
    pid_t *pidt;

    pidt = malloc(sizeof(pid_t) * size);          //malloc failed ??
    if (pidt == NULL)
        return (print_error_pidt(), NULL);

    ft_bzero(pidt, sizeof(pid_t) * size); 
    
    return (pidt);
}

static char *get_env_path(t_data *data)
{
    char *path;

    path = getenvvar("PATH", data);
    return (path);
}


/*is single cmd name only without / . ..*/
static int is_cmd_path(char *cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (cmd[i] == '/' || cmd[i] == '.') 
            return (1);
        i++;
    }
    return(0);
}

static char *get_filepath(char *env_path, char *cmd)
{
    int     i;
    char    **split_path;
    char    *command;                                        //with filepath /usr/bin/ls
    char    *copy_command;

    command = NULL;
    copy_command = NULL;
    split_path = ft_split(env_path, ':');                   //need free?
    i = 0;
    while (split_path[i])
    {
        free(command);

        command = ft_strjoin(split_path[i], "/");             // "/usr/bin" + "/"
        
        copy_command = ft_strdup(command);
        free(command);

        command = ft_strjoin(copy_command, cmd);
        free(copy_command);

        if (access(command, F_OK) == 0)
            return (free_charchar_str(split_path), command);
        i++;
    }

    free_charchar_str(split_path);
    free(command);
    return (NULL);
}

char *get_command_path(char *cmd, t_data *data)
{
    char *command;
    char *env_path;

    if (is_cmd_path(cmd) == 1)                      //  "/usr/bin/ls", "../../usr/bin/ls", "../usr/bin/"
    {
        command = ft_strdup(cmd);
        if (command == NULL)
            return (NULL);
        return (command);
    }
    env_path = get_env_path(data);                      //need check NULL?
    command = get_filepath(env_path, cmd);
    return (command);
}

/***argv = { "/bin/ls", "-l", NULL };*/
char **form_args(char *command, char **args)
{
    char **argv;
    int size;
    int i;
    int k;

    size  = get_args_len(args);
    argv = malloc(sizeof(char *) * (size + 1 + 1));    //1 for cmd, 1 for NULL
    if (argv == NULL)
        return (NULL);
    k = 0;
    argv[k] = command;                                 //1st is command
    k++;
    i = 0;
    while (args[i])
    {
        argv[k] = args[i];
        i++;
        k++;
    }
    argv[k] = NULL;
    return (argv);
}

static void print_error_heredoc()
{
    ft_putstr_fd("here doc: ", STDERR_FILENO);
    ft_putstr_fd("here doc failed !\n", STDERR_FILENO);
}

static char *get_tmp_file(int i)
{
    char *tmp_file;
    char *file;

    file = ft_itoa(i);
    tmp_file = ft_strjoin("/tmp/", file);                           // "/tmp/1"
    if (tmp_file == NULL)
    {
        print_error_heredoc();
        return (free(file), NULL);
    }
    free(file);
    return (tmp_file);
} 

int do_heredoc(t_inout *inout, int i)
{
    char *line;
    char *tmp_file;
    int  filefd;

    tmp_file = get_tmp_file(i);
    if (tmp_file == NULL)
        return (0);

    filefd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (filefd < 0)
        return (print_error_heredoc(), free(tmp_file), 0);
    while ((line = readline("> ")) != NULL) 
    {
        if (equals(line, inout->delimiter) == 1) 
        {
            free(line);
            break;
        }
        write(filefd, line, ft_strlen(line));
        write(filefd, "\n", 1);
        free(line);
    }
    close(filefd);
    inout->heredoc = tmp_file;
    return (1);
}

int is_dir(char *command) 
{
    struct stat sbuf;

    if (stat(command, &sbuf) != 0) 
        return (0);
    return S_ISDIR(sbuf.st_mode);
}