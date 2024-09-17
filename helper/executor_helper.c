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

int **get_pipe(int size)
{
    int **pipefd;
    int i;

    pipefd = malloc(sizeof(int *) * size); //??

    ft_bzero(pipefd, sizeof(int *) * size); //??

    if (pipefd == NULL)
        return (NULL);
    i = 0;
    while (i < size)
    {
        pipefd[i] = malloc(sizeof(int) * 2);
        

        if (pipefd[i] == NULL)
        {
            free_pipefd(pipefd, i);
            return (NULL);
        }
        ft_bzero(pipefd[i], sizeof(int) * 2); //??

        i++;
    }
    return (pipefd);
}

pid_t *get_pidt(int size)
{
    pid_t *pidt;

    pidt = malloc(sizeof(pid_t) * size);

    ft_bzero(pidt, sizeof(pid_t) * size); //??

    if (pidt == NULL)
        return (NULL);
    return (pidt);
}

static char *get_env_path()
{
    char *path;

    path = getenv("PATH");
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
    int     is_exist_cmd;
    //int     is_permission_ex;
    
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

        is_exist_cmd = access(command, F_OK);                    //check exe is exists
        if (is_exist_cmd == 0)                                   //yes
        {
            //is_permission_ex = access(pathexe, X_OK);         // check exe is excutable 
            //if (is_permission_ex == 0)//yes
            
            free_charchar_str(split_path);
            return (command);
        }
        i++;
    }

    free_charchar_str(split_path);
    free(command);
    return (NULL);
}

char *get_command_path(char *cmd)
{
    char *command;
    char *env_path;

    if (is_cmd_path(cmd) == 1)                      //  "/usr/bin/ls", "../../usr/bin/ls", "../usr/bin/"
        return (cmd);
    env_path = get_env_path();                      //need check NULL?
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

int do_heredoc(t_inout *inout, int i)
{
    char *line;
    char *tmp_file;
    char *file;
    int  filefd;

    file = ft_itoa(i);
    tmp_file = ft_strjoin("/tmp/", file);                           // "/tmp/1"
    free(file);

    filefd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);    //write to tmp file
    if (filefd < 0) 
    {
        perror("here doc - error open file");
        return (0);
    }

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