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

static void clean(t_data *tmp_data, char *tmp_file, int *tmp_filefd, int *tmp_pipefd, char *tmp_delimiter)
{
    close(*tmp_filefd);
    unlink(tmp_file);
    free(tmp_file);
    free(tmp_delimiter);
    close(tmp_pipefd[1]);
    free_all2(tmp_data);
    tmp_data = NULL;
    tmp_file = NULL;
    tmp_filefd = NULL;
    tmp_pipefd = NULL;
    tmp_delimiter = NULL;
}

static void cleanup_child(t_data *data, char *file, int *filefd, int pipefd[2], char *delimiter)
{
    static t_data *tmp_data;
    static char *tmp_file;
    static int *tmp_filefd;
    static int *tmp_pipefd;
    static char *tmp_delimiter;

    if (data == NULL)
    {
        if (tmp_data != NULL) 
        {
            printf("\n");
            clean(tmp_data, tmp_file, tmp_filefd, tmp_pipefd, tmp_delimiter);
            /*close(*tmp_filefd);
            unlink(tmp_file);
            free(tmp_file);
            free(tmp_delimiter);
            close(tmp_pipefd[1]);
            free_all2(tmp_data);
            tmp_data = NULL;
            tmp_file = NULL;
            tmp_filefd = NULL;
            tmp_pipefd = NULL;
            tmp_delimiter = NULL;*/
        }
    }
    else 
    {
        tmp_data = data;
        tmp_file = file;
        tmp_filefd = filefd;
        tmp_pipefd = pipefd;
        tmp_delimiter = delimiter;
    }
}

void handle_sig_child(int sig)
{
    if (sig == SIGINT)
    {
        cleanup_child(NULL, NULL, NULL, NULL, NULL);
        signal(SIGINT, SIG_DFL);
        kill(getpid(), SIGINT);
    }
}

void handle_sigint_parent(int sig)
{
    (void)sig;
}

static void warning_heredoc_eof(char *delimiter)
{
    ft_putstr_fd("here-document delimited by end-of-file (wanted ", STDERR_FILENO);
    ft_putstr_fd("'", STDERR_FILENO);
    ft_putstr_fd(delimiter, STDERR_FILENO);
    ft_putstr_fd("'", STDERR_FILENO);
    ft_putstr_fd(")\n", STDERR_FILENO);
}

static char *get_delimiter(char *inout_delimiter, int got_quotes)
{
    t_stack	stack;
    char *delimiter;

    ft_bzero(&stack, sizeof(t_stack));
    if (got_quotes == 1)
    {
        qremoval(inout_delimiter, &stack);
        delimiter = ft_strdup(stack.line);
        if (delimiter == NULL)
            return (NULL);
    }
    else
    {
        delimiter = ft_strdup(inout_delimiter);
        if (delimiter == NULL)
            return (NULL);
    }
    return (delimiter);
}

static void write_line(int got_quotes, char *line, t_data *data, int filefd)
{
    t_stack	stack;

    ft_bzero(&stack, sizeof(t_stack));
    if (got_quotes == 0)
    {
        expandss(&stack, line, data);
        write(filefd, stack.line, ft_strlen(stack.line));
    }
    else
        write(filefd, line, ft_strlen(line));
    write(filefd, "\n", 1);
}

static void do_readline(char *delimiter, int filefd, int got_quotes, t_data *data)
{
    char	*line;
    //t_stack	stack;

    //ft_bzero(&stack, sizeof(t_stack));
    while (1)
	{
		line = readline("> ");
        if (line == NULL)
        {
            warning_heredoc_eof(delimiter); //break;
            break;
        } 
        if (equals(line, delimiter) == 1)
		{
			free(line);
			break;
		}
        
        write_line(got_quotes, line, data, filefd);

        /*if (got_quotes == 0)
        {
		    expandss(&stack, line, data);
		    write(filefd, stack.line, ft_strlen(stack.line));
        }
        else
            write(filefd, line, ft_strlen(line));
        write(filefd, "\n", 1);*/


		free(line);
	}
}

static void heredoc_child(t_inout *inout, int i, int pipefd[2], t_data *data)
{
    //char	*line;
	char	*tmp_file;
	int		filefd;
	//t_stack	stack;
    int got_quotes;
    char *delimiter;

    got_quotes = is_contain_quotes(inout->delimiter);

    delimiter = get_delimiter(inout->delimiter, got_quotes);
    if (delimiter == NULL)
        return (print_error_heredoc(), exit(EXIT_FAILURE));

   /* if (got_quotes == 1)
    {
        ft_bzero(&stack, sizeof(t_stack));
        qremoval(inout->delimiter, &stack);
        delimiter = ft_strdup(stack.line);
        if (delimiter == NULL)
            return (print_error_heredoc(), exit(EXIT_FAILURE));
        ft_bzero(&stack, sizeof(t_stack));
    }
    else
    {
        delimiter = ft_strdup(inout->delimiter);
        if (delimiter == NULL)
            return (print_error_heredoc(), exit(EXIT_FAILURE));
    }*/

    //tmp_file = NULL;
	tmp_file = get_tmp_file(i);
	if (tmp_file == NULL)
		return (print_error_heredoc(), free(delimiter), exit(EXIT_FAILURE));
	filefd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (filefd < 0)
        return (print_error_heredoc(), free(tmp_file), free(delimiter), exit(EXIT_FAILURE));
    cleanup_child(data, tmp_file, &filefd, pipefd, delimiter);

    do_readline(delimiter, filefd, got_quotes, data);

    /*while (1)
	{
		line = readline("> ");
        if (line == NULL)
        {
            //warning_heredoc_eof(inout->delimiter);
            warning_heredoc_eof(delimiter);
            break;
        } 
		//if (equals(line, inout->delimiter) == 1)
        if (equals(line, delimiter) == 1)
		{
			free(line);
			break;
		}
        if (got_quotes == 0)
        {
		    expandss(&stack, line, data);
		    write(filefd, stack.line, ft_strlen(stack.line));
        }
        else
            write(filefd, line, ft_strlen(line));
		write(filefd, "\n", 1);
		free(line);
	}*/

    write(pipefd[1], tmp_file, strlen(tmp_file) + 1);

    close(filefd);
    free(delimiter);
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

static void save_heredoc_file(int pipefd[2], t_inout *inout)
{
    char *tmp_file;

    tmp_file = malloc(10 * sizeof(char));
    ft_bzero(tmp_file, 10);
    read(pipefd[0], tmp_file, 10);
    inout->heredoc = tmp_file;
    close(pipefd[0]);
    
}

static int wait_heredoc_child(int pipefd[2], t_data *data, t_inout *inout)
{
    int status;
    //char *tmp_file;

    status = 0;
    close(pipefd[1]);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT,SIG_IGN);
    wait(&status);
    if (WIFSIGNALED(status))
    {
        close(pipefd[0]);
        update_exit_status(128 + WTERMSIG(status), data);
        return (-9);
    }
    else if (WIFEXITED(status)) 
    {
        if (WEXITSTATUS(status) == 0) 
        {
            save_heredoc_file(pipefd, inout);

            /*tmp_file = malloc(10 * sizeof(char));
            ft_bzero(tmp_file, 10);
            read(pipefd[0], tmp_file, 10);
            inout->heredoc = tmp_file;
            close(pipefd[0]);*/
            update_exit_status(WEXITSTATUS(status), data);
        }
        else
            //return (WEXITSTATUS(status));
            return (close(pipefd[0]), WEXITSTATUS(status));
    }
    return (1);
}

static int do_heredoc_as_child(t_inout *inout, int i, t_data *data)
{
    //int status;
    int pipefd[2];
    pid_t   pidt;
    //char *tmp_file;

    //status = 0;
    if (pipe(pipefd) == -1) 
        return (perror("pipe failed!"), 0);
    pidt = fork();
    if (pidt == -1)
        return (perror("fork failed!"), 0);
    if (pidt == 0)
    {
        close(pipefd[0]);
        signal(SIGINT, handle_sig_child);
		signal(SIGQUIT,SIG_IGN);
        heredoc_child(inout, i, pipefd, data);
        exit(0);
    }
    else
    {
        return (wait_heredoc_child(pipefd, data, inout));

        /*close(pipefd[1]);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT,SIG_IGN);
        wait(&status);
		if (WIFSIGNALED(status))
        {
            close(pipefd[0]);
            update_exit_status(128 + WTERMSIG(status), data);
            return (-9);
        }
        else if (WIFEXITED(status)) 
        {
            if (WEXITSTATUS(status) == 0) 
            {
                tmp_file = malloc(10 * sizeof(char));
                ft_bzero(tmp_file, 10);
                read(pipefd[0], tmp_file, 10);
                inout->heredoc = tmp_file;
                close(pipefd[0]);
                update_exit_status(WEXITSTATUS(status), data);
            }
            else
                //return (WEXITSTATUS(status));
                return (close(pipefd[0]), WEXITSTATUS(status));
        }*/
    }
    return (1);
}

int  do_heredoc(t_list *cmd_list, t_data *data)
{
    t_list  *inout_list;
    t_inout *inout;
    int     i;
    int     heredoc_status;
   
    i = 0;
    while (cmd_list != NULL)
    {
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