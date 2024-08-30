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
#include "minishell.h"


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

int **get_pipe(int size)
{
    int **pipefd;
    int i;

    pipefd = malloc(sizeof(int *) * size);

    i = 0;
    while (i < size)
    {
        pipefd[i] = malloc(sizeof(int) * 2);
        i++;
    }

    return (pipefd);

}

pid_t *get_pidt(int size)
{
    pid_t *pidt;

    pidt = malloc(sizeof(pid_t) * size);

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
    char    *command;       //with filepath /usr/bin/ls
    int     is_exist_cmd;
    //int     is_permission_ex;
    
    split_path = ft_split(env_path, ':'); //need free?
    i = 0;
    while (split_path[i])
    {
        command = ft_strjoin(split_path[i], "/");   // "/usr/bin" + "/"
        command = ft_strjoin(command, cmd);  
        is_exist_cmd = access(command, F_OK);       //check exe is exists
        if (is_exist_cmd == 0)//yes
        {
            //is_permission_ex = access(pathexe, X_OK);  // check exe is excutable 
            //if (is_permission_ex == 0)//yes
                return (command);
        }
        i++;
    }
    return (NULL);
}

char *get_command_path(char *cmd)
{
    char *command;
    char *env_path;

    
    if (is_cmd_path(cmd) == 1)//  "/usr/bin/ls", "../../usr/bin/ls", "../usr/bin/"
    {
       // command = token->cmd;
        return (cmd);
    }
    env_path = get_env_path(); //need check NULL?
    command = get_filepath(env_path, cmd);
    return (command);

}

static int get_args_len(char **args)
{
    int i;

    i = 0;
    while (args[i])
        i++;
    return (i);
}

/***argv = { "/bin/ls", "-l", NULL };*/
char **form_args(char *command, char **args)
{
    char **argv;
    int size;

    int i;
    int k;

    size  = get_args_len(args);

    argv = malloc(sizeof(char *) * (size + 1 + 1)); //1 for cmd, 1 for NULL
    if (argv == NULL)  //check NULL?
        return (NULL);

    k = 0;
    argv[k] = command;   //1st is command
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
    //char *final_line;
    char *tmp_file;
    char *file;
    int  filefd;

    //tmp_file = "/tmp/";
    file = ft_itoa(i);
    tmp_file = ft_strjoin("/tmp/", file); // "/tmp/1"

    //write to tmp file
    filefd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (filefd < 0) 
    {
        perror("open");
        //exit(EXIT_FAILURE);
    }

    //final_line = "";
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