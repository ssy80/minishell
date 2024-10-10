/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 23:20:55 by ssian             #+#    #+#             */
/*   Updated: 2024/09/27 23:21:01 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void print_error_heredoc()
{
    ft_putstr_fd("here doc: ", STDERR_FILENO);
    ft_putstr_fd("here doc failed !\n", STDERR_FILENO);
}

char *get_tmp_file(int i)
{
    char *tmp_file;
    char *file;

    file = ft_itoa(i);
    tmp_file = ft_strjoin("/tmp/", file);
    if (tmp_file == NULL)
    {
        print_error_heredoc();
        return (free(file), NULL);
    }
    free(file);
    return (tmp_file);
}

static void cleanup_child(t_data *data, char *file, int *filefd, int pipefd[2])
{
    static t_data *tmp_data;// = NULL;
    static char *tmp_file; // = NULL;
    static int *tmp_filefd;// = NULL;
    static int *tmp_pipefd;// = NULL;

    if (data == NULL)
    {
        if (tmp_data != NULL) 
        {
  //  printf("\nChild: Cleaning up resources...\n");
            printf("\n");
            close(*tmp_filefd);
            unlink(tmp_file);
            free(tmp_file);
            close(tmp_pipefd[1]);
            free_all2(tmp_data);
            tmp_data = NULL;
            tmp_file = NULL;
            tmp_filefd = NULL;
            tmp_pipefd = NULL;
        }
    } 
    else 
    {
        tmp_data = data;
        tmp_file = file;
        tmp_filefd = filefd;
        tmp_pipefd = pipefd;
    }
}

void handle_sig_child(int sig)
{
    if (sig == SIGINT)
    {
//printf("--SIGITN received--\n");
        cleanup_child(NULL, NULL, NULL, NULL);
        signal(SIGINT, SIG_DFL);
        kill(getpid(), SIGINT);                                     //resend SIGINT to kill child after cleanup
    }
    /*else if (sig == SIGQUIT)
    {
        //printf("\n");
		(void)sig;
    }*/
}

void handle_sigint_parent(int sig)
{
    (void)sig;
	//printf("\n");
   /* if (sig == SIGINT)
    {
//        printf("--Parent SIGITN received--\n");
       // printf("\n");
       // cleanup(NULL, NULL, NULL, NULL);
        //signal(SIGINT, SIG_DFL);
        //kill(getpid(), SIGINT);
        //exit(2);
    }
	else if (sig == SIGQUIT)
	{

	}*/
}

static void warning_heredoc_eof(char *delimiter)
{
    ft_putstr_fd("here-document delimited by end-of-file (wanted ", STDERR_FILENO);
    ft_putstr_fd("'", STDERR_FILENO);
    ft_putstr_fd(delimiter, STDERR_FILENO);
    ft_putstr_fd("'", STDERR_FILENO);
    ft_putstr_fd(")\n", STDERR_FILENO);
}

static void heredoc_child(t_inout *inout, int i, int pipefd[2], t_data *data)
{
    char	*line;
	char	*tmp_file;
	int		filefd;
	t_stack	stack;

    tmp_file = NULL;
	tmp_file = get_tmp_file(i);
	if (tmp_file == NULL)
		return (print_error_heredoc(), exit(EXIT_FAILURE));
	filefd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (filefd < 0)
        return (print_error_heredoc(), free(tmp_file), exit(EXIT_FAILURE));
    cleanup_child(data, tmp_file, &filefd, pipefd);
    while (1)
	{
		line = readline("> ");
        if (line == NULL)
        {
            warning_heredoc_eof(inout->delimiter);
            break;
        } 
		if (equals(line, inout->delimiter) == 1)
		{
			free(line);
			break;
		}
		expandss(&stack, line, data);
		write(filefd, stack.line, ft_strlen(stack.line));
		write(filefd, "\n", 1);
		free(line);
	}
	close(filefd);
    //close(pipefd[0]);
    write(pipefd[1], tmp_file, strlen(tmp_file) + 1);
    free(tmp_file);
    free_all2(data);
    close(pipefd[1]);
}

/*static int	init_pipe_pid(pid_t *pidt, int *pipefd)
{
	if (pipe(pipefd) == -1) 
        return (perror("pipe failed!"), 0);
    pidt = fork();
    if (pidt == -1)
        return (perror("fork failed!"), 0);
}*/

static int do_heredoc_as_child(t_inout *inout, int i, t_data *data)
{
    int status;
    //int signal_num;
    int pipefd[2];
    pid_t   pidt;
    char *tmp_file;

    status = 0;

	//init_pipe_pid(pidt, pipefd);

    if (pipe(pipefd) == -1) 
        return (perror("pipe failed!"), 0);
    pidt = fork();
    if (pidt == -1)
        return (perror("fork failed!"), 0);
    if (pidt == 0)
    {
        close(pipefd[0]);
        //signal(SIGINT, SIG_DFL);
		//signal(SIGQUIT, SIG_DFL);
        signal(SIGINT, handle_sig_child);
        //signal(SIGQUIT,handle_sig_child);
		signal(SIGQUIT,SIG_IGN);
        heredoc_child(inout, i, pipefd, data);
        exit(0);
    }
    else
    {
        close(pipefd[1]);
        //signal(SIGINT, SIG_DFL);
		//signal(SIGQUIT, SIG_DFL);
        //signal(SIGINT, handle_sigint_parent);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT,SIG_IGN);
		//signal(SIGQUIT, handle_sigint_parent);
        wait(&status);
		if (WIFSIGNALED(status))                                                  // Child was terminated by a signal
        {
            close(pipefd[0]);
 //           signal_num = WTERMSIG(status);
 //           printf("Parent: Child was killed by signal %d.\n", signal_num);
  //          if (signal_num == SIGINT)
            update_exit_status(128 + WTERMSIG(status), data);
            return (-9);
        }
        else if (WIFEXITED(status)) 
        {
            if (WEXITSTATUS(status) == 0) 
            {
  //              printf("Parent: Child exited normally. Heredoc saved \n");
                tmp_file = malloc(10 * sizeof(char));
                ft_bzero(tmp_file, 10);
                read(pipefd[0], tmp_file, 10);
                inout->heredoc = tmp_file;
                close(pipefd[0]);
                update_exit_status(WEXITSTATUS(status), data);
            }
            else
                return (WEXITSTATUS(status));
        }
    }
    return (1);
}

int  do_heredoc(t_list *cmd_list, t_data *data)
{
    //t_cmd   *cmd;
    t_list  *inout_list;
    t_inout *inout;
    int     i;
    int     heredoc_status;
   
    i = 0;
    while (cmd_list != NULL)
    {
        //cmd = (t_cmd *)(cmd_list->content);
        //inout_list = cmd->inout_list;
        inout_list = ((t_cmd *)(cmd_list->content))->inout_list;
        while (inout_list != NULL)
        {
            inout = (t_inout *)(inout_list->content);
            if (inout->type == 3)                               
            {
                heredoc_status = 0;
                heredoc_status = do_heredoc_as_child(inout, i, data);
                if (heredoc_status <= 0)
                    return (heredoc_status);
            }
            i++;
            inout_list = inout_list->next;
        }
        cmd_list = cmd_list->next;
    }
    return (1);
}

/*int do_heredoc(t_inout *inout, int i)
{
	char	*line;
	char	*tmp_file;
	int		filefd;

	tmp_file = get_tmp_file(i);
	if (tmp_file == NULL)
		return (0);
	filefd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (filefd < 0)
		return (print_error_heredoc(), free(tmp_file), 0);

	//while ((line = readline("> ")) != NULL)
	//while ((line = readline("> ")) != NULL) 
	while (1)
	{
		line = readline("> ");

		//if (g_var == 130)
		//{
		//	printf("\nCtrl+C pressed, exiting...\n");
            //free(input);  // Clean up memory
        //    break;
		//}
		
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
	//printf("heredoc: %s\n", inout->heredoc);
	return (1);
}*/

/*int do_heredoc(t_inout *inout, int i)
{
	char	*line;
	char	*tmp_file;
	int		filefd;

	tmp_file = get_tmp_file(i);
	if (tmp_file == NULL)
		return (0);
	filefd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (filefd < 0)
		return (print_error_heredoc(), free(tmp_file), 0);

	//while ((line = readline("> ")) != NULL)
	//while ((line = readline("> ")) != NULL) 
	while (1)
	{
		line = readline("> ");

		//if (g_var == 130)
		//{
		//	printf("\nCtrl+C pressed, exiting...\n");
            //free(input);  // Clean up memory
        //    break;
		//}
		
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
	//printf("heredoc: %s\n", inout->heredoc);
	return (1);
}*/