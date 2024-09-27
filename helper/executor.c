/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:20:22 by ssian             #+#    #+#             */
/*   Updated: 2024/08/28 16:20:23 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void unlink_file(char *filepath)
{
    if (unlink(filepath) == -1) 
    {
        perror("unlink");
    }
}

static void do_inout(t_list *inout_list, t_data *data)
{
    t_inout *inout;
    int filefd;

    while (inout_list != NULL)
    {
        inout = (t_inout *)(inout_list->content);
        if (inout->type == 2)                                                //2=infile
        {
            filefd = open(inout->file, O_RDONLY);
            if (filefd < 0) 
            {
                perror(inout->file);
                free_all(data);
                exit(EXIT_FAILURE);
            }
            dup2(filefd, STDIN_FILENO);
            close (filefd);
        }
        else if (inout->type == 0)                                            //0=create
        {
            filefd = open(inout->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (filefd < 0) 
            {
                perror(inout->file);
                free_all(data);
                exit(EXIT_FAILURE);
            }
            dup2(filefd, STDOUT_FILENO);
            close (filefd);
        }
        else if (inout->type == 1)                                             //1=append
        {
            filefd = open(inout->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (filefd < 0) 
            {
                perror(inout->file);
                free_all(data);
                exit(EXIT_FAILURE);
            }
            dup2(filefd, STDOUT_FILENO);
            close (filefd);
        }
        else if (inout->type == 3)                                             //3=heredoc
        {
            filefd = open(inout->heredoc, O_RDONLY);
            if (filefd < 0) 
            {
                perror(inout->heredoc);
                //unlink_file(inout->heredoc);
                //free(inout->heredoc);
                //inout->heredoc = NULL;
                free_all(data);
                exit(EXIT_FAILURE);
            }
            dup2(filefd, STDIN_FILENO);
            close (filefd);
            //unlink_file(inout->heredoc);
            //free(inout->heredoc);
            //inout->heredoc = NULL;
            /*if (unlink(inout->heredoc) == -1) 
            {
                perror("unlink");
                //exit(EXIT_FAILURE);
            }*/
        }
        inout_list = inout_list->next;
    }
}

static void do_builtin(t_cmd *cmd, t_data *data)
{
    if (equals(cmd->cmd, "echo") == 1)
        builtin_echo(cmd->args);
    else if (equals(cmd->cmd, "cd") == 1)
        builtin_cd(cmd->args, data);
        /*if (builtin_cd(cmd->args, data) == 0)                   //0 = failure
        {
            ft_putstr_fd("cd: ", STDERR_FILENO);
            ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
        }*/
    else if (equals(cmd->cmd, "pwd") == 1)
        builtin_pwd();
    else if (equals(cmd->cmd, "export") == 1)
        builtin_export(cmd->args, data);
        /*if (builtin_export(cmd->args, data) == 0)                 //0 = failure
        {
            ft_putstr_fd("export: ", STDERR_FILENO);
            ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
        }*/
    else if (equals(cmd->cmd, "unset") == 1)
        builtin_unset(cmd->args, data);
        /*if (builtin_unset(cmd->args, data) == 0)                  //0 = failure
        {
            ft_putstr_fd("unset: ", STDERR_FILENO);
            ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
        }*/
    else if (equals(cmd->cmd, "env") == 1)
        builtin_get_env(cmd->args, data);
    else if (equals(cmd->cmd, "exit") == 1)
        builtin_exit(cmd->args, data);
}


/*static char **dup_args(char **args)
{
    char **new_args;
    char *arg;
    int size;
    int i;

    size = get_args_len(args);
    new_args = malloc(sizeof(char *) * (size + 1));

print_args(args);

    i = 0;
    while (args[i])
    {
        arg = ft_strdup(args[i]);
        printf("arg: %s\n", arg);
        if (arg == NULL)
        {
            free_charchar_str(new_args);
            return(NULL);
        }
        new_args[i] = arg;
        i++;
    }
    new_args[i] = NULL;

    print_args(new_args);
    return (new_args);
}*/

static void error_command_is_dir(t_cmd *cmd, t_data *data)
{
    ft_putstr_fd(cmd->cmd, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd("Is a directory\n", STDERR_FILENO);
    free_all(data);
    exit(126);
}

static void error_no_command(t_cmd *cmd, t_data *data)
{
    ft_putstr_fd(cmd->cmd, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd("command not found\n", STDERR_FILENO);
    free_all(data);
    exit(127);
}

static void error_no_env(t_cmd *cmd, t_data *data)
{
    ft_putstr_fd(cmd->cmd, STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
    free_all(data);
    exit(EXIT_FAILURE);
}

static void do_command(t_cmd *cmd, t_data *data)
{
    char *command;
    char    **envp;

    if (is_dir(cmd->cmd) == 1)
        error_command_is_dir(cmd, data);
        /*ft_putstr_fd(cmd->cmd, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putstr_fd("Is a directory\n", STDERR_FILENO);
        free_all(data);
        exit(126);*/
    
    command = get_command_path(cmd->cmd, data);
    if (command == NULL)
    //{
        error_no_command(cmd, data);
        /*ft_putstr_fd(cmd->cmd, STDERR_FILENO);
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putstr_fd("command not found\n", STDERR_FILENO);
        free_all(data);
        exit(127);*/
    //}
    else
    {
        envp = get_current_env(data);
        if (envp == NULL)
            error_no_env(cmd, data);
            /*ft_putstr_fd(cmd->cmd, STDERR_FILENO);
            ft_putstr_fd(": ", STDERR_FILENO);
            ft_putstr_fd("malloc failed!\n", STDERR_FILENO);
            free_all(data);
            exit(EXIT_FAILURE);*/
        if (execve(command, cmd->args, envp) == -1) 
        {
            perror(cmd->cmd);
            free(envp);
            free(command);
            free_all(data);
            if (errno == 2)
                exit(127);
            else
                exit(EXIT_FAILURE);
        }
    }
}

static int do_single_cmd(t_cmd *cmd, t_data *data)
{
    pid_t pidt;
    int status;
    
    pidt = fork();
    if (pidt == -1) 
    {
        perror("fork failed!");
        free_all(data);    
        exit(EXIT_FAILURE);
    }

    if (pidt == 0)
    {
        if (cmd->inout_list != NULL)
            do_inout(cmd->inout_list, data);

        if (cmd->cmd != NULL)
        {
            if (is_builtin_fn(cmd->cmd) == 1)
            {
                if(equals(cmd->cmd, "env") == 1)
                   builtin_get_env(cmd->args, data);
                
                if (equals(cmd->cmd, "pwd") == 1)
                    getpwd();

                if (equals(cmd->cmd, "echo") == 1)
                    builtin_echo(cmd->args);
            
            }
            else
                do_command(cmd, data);
        }

        free_all(data);        
        exit(EXIT_SUCCESS);
    }
    else
    {
                                                                   
        if(equals(cmd->cmd, "export") == 1)
            builtin_export(cmd->args, data);
        else if(equals(cmd->cmd, "unset") == 1)
            builtin_unset(cmd->args, data);
        else if(equals(cmd->cmd, "cd") == 1)
            builtin_cd(cmd->args, data);
        else if(equals(cmd->cmd, "exit") == 1)
            builtin_exit(cmd->args, data);

        
        //wait(NULL);
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("exit status: %d\n", WEXITSTATUS(status));
            update_exit_status(WEXITSTATUS(status), data);
        }

    }
    return (1);
}

static void do_command_first(t_cmd *cmd, int pipefd_out[], pid_t pidt, t_data *data)
{
    pidt = fork();
    if (pidt == -1) 
    {
        perror("fork failed!");
        free_all(data); 
        exit(EXIT_FAILURE);
    }

    if (pidt == 0) 
    {
        close(pipefd_out[0]);
        dup2(pipefd_out[1], STDOUT_FILENO);     
        close(pipefd_out[1]);

        if (cmd->inout_list != NULL)
            do_inout(cmd->inout_list, data);

        if (cmd->cmd != NULL)
        {
            if (is_builtin_fn(cmd->cmd) == 1)
                do_builtin(cmd, data);
            else
                do_command(cmd, data);
        }

        free_all(data);
        exit(EXIT_SUCCESS);

    }
    else
    {
        //1st cmd no need close pipe
    }
    //return (1);
    
}

static void do_command_mid(t_cmd *cmd, int pipefd_in[], int pipefd_out[], pid_t pidt, t_data *data)  
{
    pidt = fork();
    if (pidt == -1) 
    {
        perror("fork failed!");
        free_all(data);
        exit(EXIT_FAILURE);
    }

    if (pidt == 0) 
    {
        close(pipefd_in[1]);
        close(pipefd_out[0]);

        dup2(pipefd_in[0], STDIN_FILENO);
        close(pipefd_in[0]);
        dup2(pipefd_out[1], STDOUT_FILENO);
        close(pipefd_out[1]);

        if (cmd->inout_list != NULL)
            do_inout(cmd->inout_list, data);

        if (cmd->cmd != NULL)
        {
            if (is_builtin_fn(cmd->cmd) == 1)
                do_builtin(cmd, data);
            else
                do_command(cmd, data);
        }

        free_all(data);
        exit(EXIT_SUCCESS);
    }
    else
    {
        
        //2nd close in pipe.
        close(pipefd_in[0]);
        close(pipefd_in[1]);
    }

    //return (1);
}

static void do_command_last(t_cmd *cmd, int pipefd_in[], pid_t pidt, t_data *data)          
{
    pidt = fork();
    if (pidt == -1) 
    {
        perror("fork failed!");
        free_all(data); 
        exit(EXIT_FAILURE);
    }

    if (pidt == 0) 
    {
        close(pipefd_in[1]);

        dup2(pipefd_in[0], STDIN_FILENO);
        close(pipefd_in[0]);

        if (cmd->inout_list != NULL)
            do_inout(cmd->inout_list, data);

        if (cmd->cmd != NULL)
        {
            if (is_builtin_fn(cmd->cmd) == 1)
                do_builtin(cmd, data);
            else
                do_command(cmd, data);
        }

        free_all(data);
        exit(EXIT_SUCCESS);
    }
    else
    {
        
        //last cmd, close in pipe
        close(pipefd_in[0]);
        close(pipefd_in[1]);
    }
    //return (1);
    
}

static int process_heredoc(t_list *cmd_list)
{
    t_cmd   *cmd;
    t_list  *inout_list;
    t_inout *inout;
    int     i;

    i = 0;
    while (cmd_list != NULL)
    {
        cmd = (t_cmd *)(cmd_list->content);
        inout_list = cmd->inout_list;
          
        while (inout_list != NULL)
        {
            inout = (t_inout *)(inout_list->content);

            if (inout->type == 3)                               //3=heredoc
            {
                if (do_heredoc(inout, i) == 0)
                    return (0);
                /*{
                    ft_putstr_fd("here doc: ", STDERR_FILENO);
                    ft_putstr_fd("here doc failed !\n", STDERR_FILENO);
                    return (0);
                }*/
            }
            i++;
            inout_list = inout_list->next;
        }
        cmd_list = cmd_list->next;
    }
    return (1);
}

/*static t_cmd *populate_cmd(t_cmd *cmd)
{
    char    *command;

    command = get_command_path(cmd->cmd);
 
    if (command == NULL)
    {
        cmd->cmd = NULL;
        //printf("No such command\n");                     //exit after this?
    }
    else
    {
        cmd->cmd = command;
    }
    return (cmd);
}*/

static void wait_process_end(pid_t *pidt, int size, t_data *data)
{
    int i;
    int status;

    i = 0;
    while (i < size)
    {
        //waitpid(pidt[i], NULL, 0);
        waitpid(pidt[i], &status, 0);
        if (WIFEXITED(status))
        {
            printf("exit status: %d\n", WEXITSTATUS(status));
            update_exit_status(WEXITSTATUS(status), data);
        }
        i++;
    }
}

int process_cmd_list(t_list *cmd_list, t_data *data)
{
    t_cmd   *cmd;
    int     **pipefd;
    int     size;
    int     i;
    pid_t   *pidt;

    if (process_heredoc(cmd_list) == 0)               //here doc failure
        return (0);

    size = ft_lstsize(cmd_list);

    pipefd = get_pipe(size - 1);                       //if size = 0 how? return non-null pointer
    if (pipefd == NULL)
        return (0);

    pidt = get_pidt(size);
    if (pidt == NULL)
        return (0);

    data->pipefd = pipefd;
    data->pidt = pidt;

    i = 0;
    if (size == 1)                                    //only 1 command
    {
        cmd = (t_cmd *)(cmd_list->content);
        do_single_cmd(cmd, data);
    }
    else if (size > 1)                               //multiple command
    {
        while (cmd_list != NULL)
        {
            cmd = (t_cmd *)(cmd_list->content);

            if (i != (size-1))
            {
                if (pipe(pipefd[i]) == -1) 
                {
                    perror("pipe create failed!");
                    break;
                }
            }

            if(i == 0)                                                        //first cmd
                do_command_first(cmd, pipefd[i], pidt[i], data);
            /*{                                  
                if (do_command_first(cmd, pipefd[i], pidt[i], data) == 0)
                    break;
            }*/
            else if (i == (size-1))                                           //last cmd
                do_command_last(cmd, pipefd[i-1], pidt[i], data);
            /*{
                if (do_command_last(cmd, pipefd[i-1], pidt[i], data) == 0)
                    break;
            }*/
            else                                                              //middle cmd
                do_command_mid(cmd, pipefd[i-1], pipefd[i], pidt[i], data);
            /*{
                if (do_command_mid(cmd, pipefd[i-1], pipefd[i], pidt[i], data) == 0)
                    break;
            }*/
            cmd_list = cmd_list->next;
            i++;
        }

        wait_process_end(pidt, size, data);
    }

    free_pidt(pidt);
    free_pipefd_all(pipefd, size - 1);

    return (1);
}