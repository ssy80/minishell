/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:04:06 by ssian             #+#    #+#             */
/*   Updated: 2024/08/16 11:04:11 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"



static int get_arg_len(char **child_args)
{
    int i;

    i = 0;
    while (child_args[i])
        i++;
    return (i);
}

/***argv = { "/bin/ls", "-l", NULL };*/
static char **form_argv(t_list *cmd_list, char **child_args)
{
    char **argv;
    t_token *token;
    int size;
    int i;
    int k;

    token = (t_token *)(cmd_list->content);

    size  = get_arg_len(child_args);
    argv = malloc(sizeof(char *) * (size + 1 + 1)); //1 for cmd, 1 for NULL
    if (argv == NULL)
        return (NULL);
    k = 0;
    argv[k] = token->cmd;
    k++;
    i = 0;
    while (child_args[i])
    {
        argv[k] = child_args[i];
        i++;
        k++;
    }
    argv[k] = NULL;
    return (argv);
}

static char *get_env_path()
{
    char *path;

    path = getenv("PATH");

    return (path);
}


static char *get_pathexe(t_list *cmd_list)
{
    char *pathexe;
    char *path;
    t_token *token;
    char **split_path;
    int i;
    int ret;

    token = (t_token *)(cmd_list->content);
    path = get_env_path();
    //printf("PATH: %s\n", path);

    if (path != NULL)
    {
        split_path = ft_split(path, ':');
        /*i = 0;
        while (split_path[i])
        {
            printf("path: %s\n", split_path[i]);
            i++;
        }*/

        i = 0;
        while (split_path[i])
        {
            pathexe = ft_strjoin(split_path[i], "/");
            pathexe = ft_strjoin(pathexe, token->cmd);
            /*printf("split_path[i]: %s\n", split_path[i]);
            printf("token->cmd: %s\n", token->cmd);*/
            //printf("pathexe: %s\n", pathexe);
            ret = access(pathexe, F_OK); //check exe is exists
            if (ret == 0)//yes
            {
                ret = access(pathexe, X_OK);  // check exe is excutable 
                if (ret == 0)//yes
                {
                    return (pathexe);
                }
            }
            i++;
        }
    }
    return (NULL);
}

char *do_other(t_list *cmd_list, char **child_args)
{
   // t_token *token;
    char **argv; //= { "/bin/ls", "-l", NULL };
    char **envp = { NULL };
    char *output;
    char *pathexe;   // path to the cmd executable e.g /usr/bin/ls

    //output = NULL;
    // token = (t_token *)(cmd_list->content); //get cmd to execute
    argv = form_argv(cmd_list, child_args);
    pathexe = get_pathexe(cmd_list);

    if (pathexe == NULL)
    {
        return ("error executing cmd\n");
    }

    /*int i = 0;
    while (argv[i])
    {
        printf("args: %s\n", argv[i]);
        i++;
    }*/

    int fd[2];
    pid_t pid;
    char buffer[1024];
    size_t count;

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        // Close the read end of the pipe
        close(fd[0]);

        // Redirect stdout to the write end of the pipe
        dup2(fd[1], STDOUT_FILENO);
        
        // Close the write end of the pipe (after it's been duplicated)
        close(fd[1]);

        // Prepare arguments for execve
        //char *argv[] = { "/bin/ls", "-l", NULL };
        //char *envp[] = { NULL };  // No special environment variables

        // Execute the program
        //execve("/bin/ls", argv, envp);
        //execve(token->cmd, argv, envp);
        execve(pathexe, argv, envp);

        // If execve() fails
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        // Close the write end of the pipe
        close(fd[1]);

        // Read the output from the child process
        while ((count = read(fd[0], buffer, sizeof(buffer) - 1)) > 0) 
        {
            buffer[count] = '\0';  // Null-terminate the string
            //printf("Output from child process:\n%s", buffer);
        }
        output = buffer;

        // Close the read end of the pipe
        close(fd[0]);

        // Wait for the child process to finish
        wait(NULL);
    }

    /*char *args[] = {"ls", "-l", "-a", (char *)0};
    char *env_args[] = {(char*)0};
    execve(args[0], args, env_args);*/
    return (output);
}