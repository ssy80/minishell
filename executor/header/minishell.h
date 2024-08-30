/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssian <ssian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 15:37:31 by ssian             #+#    #+#             */
/*   Updated: 2024/08/12 15:37:38 by ssian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <bits/sigaction.h>

#include "libft.h"


typedef struct s_inout
{
	int		type;               //0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
	char	*file;				//for 0=create(>), 1=append(>>), 2=infile(<)
	char	*heredoc;			//for heredoc tmp file
	char	*delimiter;         //for heredoc delimiter
}	t_inout;


/* e.g cmd: ls -l -a | grep zz | wc > a
   break to 3 cmd 
   1) ls -l -a   (**args= {"-l", "-a", NULL})
   2) grep zz    (**args= {"zz", NULL})  
   3) wc > a     (**args=NULL, inout_list = {t_inout={type=0;file="a";heredoc=NULL;delimiter=NULL}, ... , ...}
*/
typedef struct s_cmd
{
	char		*cmd;           // e.g ls , /usr/bin/ls   - cmd name or path
	char		**args;         //     {"-l", "-a", NULL}
	t_list	    *inout_list;    //list of inout = < a > b >>c <<E in a command
}   t_cmd;

void process_cmd_list(t_list *cmd_list);
char *get_command_path(char *cmd);
char **form_args(char *command, char **args);
void print_args(char **args);
void print_cmd(t_list *cmd_list);
int **get_pipe(int size);
int do_heredoc(t_inout *inout, int i);
int equals(char *s1, char *s2);
pid_t *get_pidt(int size);
#endif
