/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:49:50 by yoong             #+#    #+#             */
/*   Updated: 2024/08/02 17:50:29 by yoong            ###   ########.fr       */
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

// # define PROMPT "ftShell :"
# define MAXLEN 512
# define PTMAX 1024
# define CDERR "No such file or directory\n"
# define MFAIL "Malloc failure\n"
# define M_MAX "Too many malloc pointer\n"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	t_list	*env;
	char	*buf;
	void	*freept[PTMAX];
	int		ptno;
	int		tkn[MAXLEN][2];
	int		itr;
}	t_data;

//lexer token e.g cat "hello" > test.txt
//cmd = cat
//arg = "hello"
//type = 0 //cmd
//type = 1 //arguments
//type = 2 //operator
typedef struct s_token
{
	char			*cmd;
	char			*arg;
	char			*operator;
	int				type;			
}	t_token;

extern int	g_var;

// ft
void	ft_bzero(void *b, size_t len);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	*ft_calloc(size_t number, size_t size);
// signal
void	handle_signal(int signum, siginfo_t *info, void *context);
void	server(void);
// cl - clean up
void	freenull(void *pt);
void	exitcl(int code);
void	setfreept(t_data *data, void *pt);
void	freenullall(t_data *data);
// built in function
void	getpwd(void);
void	getmyenv(t_data *data);
void	exitcommand(char *input, t_data *data);
void	getcd(char *buf);
int		builtin_func(char *buf, t_data *data);
char	*getenvvar(char *var, t_data *data);
// init
void	initfd(char *dir);
void	initdata(char buf[MAXLEN], char **env, t_data *data);
// shell
void	getprompt(char *dir);
void	parsecmd(t_data *data, int i, int start);

//lexer/parser/executor
t_list *process_raw_input(char *str);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void    print_token_list(t_list *token_list);
void parse_token_list(t_list **token_list);
int equals(char *s1, char *s2);
void	lstremove_last(t_list **lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void    execute_list(t_list *token_list);
char *do_other(t_list *cmd_list, char **child_args);
char	*ft_strjoin(char const *s1, char const *s2);
#endif
