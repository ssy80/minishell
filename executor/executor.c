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
#include "minishell.h"

static void do_inout(t_list *inout_list)
{
    t_inout *inout;
    int filefd;

    while (inout_list != NULL)
    {
        inout = (t_inout *)(inout_list->content);
        if (inout->type == 2) //2=infile
        {
            filefd = open(inout->file, O_RDONLY);
            if (filefd < 0) 
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(filefd, STDIN_FILENO);
            close (filefd);
        }
        else if (inout->type == 0) //0=create
        {
            filefd = open(inout->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (filefd < 0) 
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(filefd, STDOUT_FILENO);
            close (filefd);
        }
        else if (inout->type == 1) //1=append
        {
            filefd = open(inout->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (filefd < 0) 
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(filefd, STDOUT_FILENO);
            close (filefd);
        }
        else if (inout->type == 3) //3=heredoc
        {
            filefd = open(inout->heredoc, O_RDONLY);
            if (filefd < 0) 
            {
                perror("open");
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

static void do_single_cmd(t_cmd *cmd, pid_t pidt)
{
    char    **envp = { NULL };
    
    if ((pidt = fork()) == -1) 
    {
        perror("fork pidt failed");
        exit(EXIT_FAILURE);
    }

    if (pidt == 0) 
    {

        //any inoutlist?
        if (cmd->inout_list != NULL)
        {
            do_inout(cmd->inout_list);
        }

        if (execve(cmd->cmd, cmd->args, envp) == -1) 
        {
            perror("do_single_cmd execve failed");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        //no pipe to close
    }

}

void do_command1(t_cmd *cmd, int pipefd_out[], pid_t pidt) //first cmd
{
    char    **envp = { NULL };

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

        if (execve(cmd->cmd, cmd->args, envp) == -1) 
        {
            perror("do_command execve failed");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        //1st cmd no need close pipe
    }
    
}

void do_command2(t_cmd *cmd, int pipefd_in[], int pipefd_out[], pid_t pidt)  //middle cmd
{
    char    **envp = { NULL };

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

        if (execve(cmd->cmd, cmd->args, envp) == -1) 
        {
            perror("do_command execve failed");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        //2nd close in pipe.
        close(pipefd_in[0]);
        close(pipefd_in[1]);
    }
}

void do_command3(t_cmd *cmd, int pipefd_in[], pid_t pidt) //last 
{
    char    **envp = { NULL };

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

        if (execve(cmd->cmd, cmd->args, envp) == -1) 
        {
            perror("do_command execve failed");
            exit(EXIT_FAILURE);
        }
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

            if (inout->type == 3) //3=heredoc
            {
                do_heredoc(inout, i);
            }
            i++;
            inout_list = inout_list->next;
        }
        cmd_list = cmd_list->next;
    }
}

void process_cmd_list(t_list *cmd_list)
{
    t_cmd   *cmd;
    char    *command;
    char    **args;
    int     **pipefd;
    int     size;
    int     i;
    pid_t   *pidt;

    size = ft_lstsize(cmd_list);

    pipefd = get_pipe(size - 1);
    pidt = get_pidt(size);

    process_heredoc(cmd_list);
    print_cmd(cmd_list);

    i = 0;
    if (size == 1)
    {
        cmd = (t_cmd *)(cmd_list->content);

        command = get_command_path(cmd->cmd);
        printf("command: %s\n", command);
        if (command == NULL)
        {
            printf("No such command"); //exit after this?
        }
        else
        {
            //form args
            args = form_args(command, cmd->args);
            print_args(args);
            cmd->cmd = command;
            cmd->args = args;
            do_single_cmd(cmd, pidt[i]);
        }

    }
    else if (size > 1)
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

            if (cmd->cmd != NULL)     //cmd = ls or /usr/bin/ls or ../ssian/bin/abc
            {
                //form cmds
                command = get_command_path(cmd->cmd);
                printf("command: %s\n", command);
                if (command == NULL)
                {
                    printf("No such command"); //exit after this?
                }
                else
                {
                    //form args
                    args = form_args(command, cmd->args);
                    print_args(args);
                    cmd->cmd = command;
                    cmd->args = args;

                    if(i == 0)
                    {
                        printf("--1--\n");
                        do_command1(cmd, pipefd[i], pidt[i]);
                    }
                    else if (i == (size-1)) //last
                    {
                        printf("--2--\n");
                        do_command3(cmd, pipefd[i-1], pidt[i]);
                    }
                    else //middle
                    {
                        printf("--3--\n");
                        do_command2(cmd, pipefd[i-1], pipefd[i], pidt[i]);
                    }
                }
                
            }
            cmd_list = cmd_list->next;
            i++;
        }
    }

    i = 0;
    while (i < size)
    {
        waitpid(pidt[i], NULL, 0);
        i++;
    }
}

