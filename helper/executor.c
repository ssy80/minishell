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

static void do_inout(t_list *inout_list)
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
                exit(EXIT_FAILURE);
            }
            dup2(filefd, STDIN_FILENO);
            close (filefd);
            if (unlink(inout->heredoc) == -1) 
            {
                perror("unlink");
                exit(EXIT_FAILURE);
            }
        }
        inout_list = inout_list->next;
    }
}

static void do_single_cmd(t_cmd *cmd)
{
    char    **envp = { NULL };
    pid_t pidt;
    char   *command;
    
    if ((pidt = fork()) == -1) 
    {
        perror("fork pidt failed");
        exit(EXIT_FAILURE);
    }
    if (pidt == 0) 
    {
        if (cmd->inout_list != NULL)
        {
            do_inout(cmd->inout_list);
        }

        if (cmd->cmd != NULL)
        {
            if (is_dir(cmd->cmd) == 1)
            {
                ft_putstr_fd(cmd->cmd, STDERR_FILENO);
                ft_putstr_fd(": ", STDERR_FILENO);
                ft_putstr_fd("Is a directory\n", STDERR_FILENO);
                exit(EXIT_FAILURE);
            }

            command = get_command_path(cmd->cmd);

            if (command == NULL)
            {
                ft_putstr_fd(cmd->cmd, STDERR_FILENO);
                ft_putstr_fd(": ", STDERR_FILENO);
                ft_putstr_fd("command not found\n", STDERR_FILENO);
                exit(EXIT_FAILURE);
            }
            else
            {
                if (execve(command, cmd->args, envp) == -1) 
                {
                    perror(cmd->cmd);
                    free(command);
                    exit(EXIT_FAILURE);
                }
                free(command);
            }
        }

        exit(EXIT_SUCCESS);
    }
    else
    {
        wait(NULL);
    }
}

void do_command_first(t_cmd *cmd, int pipefd_out[], pid_t pidt)//, int *saved_stdout) //first cmd
{
    char    **envp = { NULL };
    char    *command;

    if ((pidt = fork()) == -1) 
    {
        perror("fork pidt failed");
        exit(EXIT_FAILURE);
    }

    if (pidt == 0) 
    {
        close(pipefd_out[0]);

        dup2(pipefd_out[1], STDOUT_FILENO);     
        close(pipefd_out[1]);

        if (cmd->inout_list != NULL)
        {
            do_inout(cmd->inout_list);
        }

        if (cmd->cmd != NULL)
        {
            if (is_dir(cmd->cmd) == 1)
            {
                ft_putstr_fd(cmd->cmd, STDERR_FILENO);
                ft_putstr_fd(": ", STDERR_FILENO);
                ft_putstr_fd("Is a directory\n", STDERR_FILENO);
                exit(EXIT_FAILURE);
            }

            command = get_command_path(cmd->cmd);

            if (command == NULL)
            {
                ft_putstr_fd(cmd->cmd, STDERR_FILENO);
                ft_putstr_fd(": ", STDERR_FILENO);
                ft_putstr_fd("command not found\n", STDERR_FILENO);
                exit(EXIT_FAILURE);
            }
            else
            {
                if (execve(command, cmd->args, envp) == -1) 
                {
                    perror(cmd->cmd);
                    free(command);
                    exit(EXIT_FAILURE);
                }
                free(command);
            }
        }

        exit(EXIT_SUCCESS);

    }
    else
    {
        //1st cmd no need close pipe
    }
    
}

void do_command_mid(t_cmd *cmd, int pipefd_in[], int pipefd_out[], pid_t pidt)  
{
    char    **envp = { NULL };
    char *command;

    if ((pidt = fork()) == -1) 
    {
        perror("fork pidt failed");
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
        {
            do_inout(cmd->inout_list);
        }

        if (cmd->cmd != NULL)
        {
            if (is_dir(cmd->cmd) == 1)
            {
                ft_putstr_fd(cmd->cmd, STDERR_FILENO);
                ft_putstr_fd(": ", STDERR_FILENO);
                ft_putstr_fd("Is a directory\n", STDERR_FILENO);
                exit(EXIT_FAILURE);
            }

            command = get_command_path(cmd->cmd);

            if (command == NULL)
            {
                ft_putstr_fd(cmd->cmd, STDERR_FILENO);
                ft_putstr_fd(": ", STDERR_FILENO);
                ft_putstr_fd("command not found\n", STDERR_FILENO);
                exit(EXIT_FAILURE);
            }
            else
            {
                if (execve(command, cmd->args, envp) == -1) 
                {
                    perror(cmd->cmd);
                    free(command);
                    exit(EXIT_FAILURE);
                }
                free(command);
            }
        }

        exit(EXIT_SUCCESS);
    }
    else
    {
        //2nd close in pipe.
        close(pipefd_in[0]);
        close(pipefd_in[1]);
    }
}

void do_command_last(t_cmd *cmd, int pipefd_in[], pid_t pidt)          
{
    char    **envp = { NULL };
    char *command;

    if ((pidt = fork()) == -1) 
    {
        perror("fork pidt failed");
        exit(EXIT_FAILURE);
    }

    if (pidt == 0) 
    {
        close(pipefd_in[1]);

        dup2(pipefd_in[0], STDIN_FILENO);
        close(pipefd_in[0]);

        if (cmd->inout_list != NULL)
        {
            do_inout(cmd->inout_list);
        }

        if (cmd->cmd != NULL)
        {
            if (is_dir(cmd->cmd) == 1)
            {
                ft_putstr_fd(cmd->cmd, STDERR_FILENO);
                ft_putstr_fd(": ", STDERR_FILENO);
                ft_putstr_fd("Is a directory\n", STDERR_FILENO);
                exit(EXIT_FAILURE);
            }

            command = get_command_path(cmd->cmd);

            if (command == NULL)
            {
                ft_putstr_fd(cmd->cmd, STDERR_FILENO);
                ft_putstr_fd(": ", STDERR_FILENO);
                ft_putstr_fd("command not found\n", STDERR_FILENO);
                exit(EXIT_FAILURE);
            }
            else
            {
                if (execve(command, cmd->args, envp) == -1) 
                {
                    perror(cmd->cmd);
                    free(command);
                    exit(EXIT_FAILURE);
                }
                free(command);
            }
        }

        exit(EXIT_SUCCESS);
    }
    else
    {
        //last cmd, close in pipe
        close(pipefd_in[0]);
        close(pipefd_in[1]);
    }
    
}

static void process_heredoc(t_list *cmd_list)
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
                do_heredoc(inout, i);
            }
            i++;
            inout_list = inout_list->next;
        }
        cmd_list = cmd_list->next;
    }
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

static void wait_process_end(pid_t *pidt, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        waitpid(pidt[i], NULL, 0);
        i++;
    }
}

void process_cmd_list(t_list *cmd_list)
{
    t_cmd   *cmd;
    int     **pipefd;
    int     size;
    int     i;
    pid_t   *pidt;

    size = ft_lstsize(cmd_list);

    pipefd = get_pipe(size - 1);
    pidt = get_pidt(size);

    process_heredoc(cmd_list);

    i = 0;
    if (size == 1)                               //only 1 command
    {
        cmd = (t_cmd *)(cmd_list->content);
        do_single_cmd(cmd);
    }
    else if (size > 1)                          //multiple command
    {
        while (cmd_list != NULL)
        {
            cmd = (t_cmd *)(cmd_list->content);

            if (i != (size-1))
            {
                if (pipe(pipefd[i]) == -1) 
                {
                    perror("pipe1 failed");
                    exit(EXIT_FAILURE);
                }
            }

            if(i == 0)                                              //first cmd
            {                                  
                do_command_first(cmd, pipefd[i], pidt[i]);
            }
            else if (i == (size-1))                                   //last cmd
            {
                do_command_last(cmd, pipefd[i-1], pidt[i]);
            }
            else                                                      //middle cmd
            {
                do_command_mid(cmd, pipefd[i-1], pipefd[i], pidt[i]);
            }
            cmd_list = cmd_list->next;
            i++;
        }

        wait_process_end(pidt, size);
    }

    free_pidt(pidt);
    free_pipefd_all(pipefd, size - 1);
}