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
# define MAXARGS 10
# define EXEC 1
# define REDIR 2
# define PIPE 3
# define PIPESYM 1
# define MSYM 2
# define LSYM 3
# define MMSYM 4
# define LLSYM 5
# define CHARSYM 6
# define NUMSYM 7
# define ERRSYM -1

typedef struct s_cmd
{
	int type;
}	t_cmd;

typedef struct s_execcmd {
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
}	t_execcmd;

typedef struct s_redircmd {
	int type;
	t_cmd *cmd;
	char *file;
	int mode;
	int fd;
}	t_redircmd;

typedef struct s_pipecmd {
	int type;
	t_cmd *left;
	t_cmd *right;
}	t_pipecmd;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;


// env = env variable
// buf hold the cmd entered
// freept is the linked list of pt to be free
// number of ptno as there is a limit of PTMAX
// tkn is 2d array with start and end index (end is exclusive) of tkn
// itr is token number
// cmd is array of tkn split using malloc allocated mem
// tkn_no is number of tkn processed
typedef struct s_data
{
	t_list	*env;
	char	*buf;
	void	*freept[PTMAX];
	int		ptno;
	int		tkn[MAXLEN][2];
	int		itr;
	char	*cmd[MAXLEN];
	int		tkn_no;
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
int		ft_isalpha(int a);
int		ft_isalnum(int a);
void	ft_bzero(void *b, size_t len);
void	*ft_calloc(size_t number, size_t size);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void*));
// signal
void	handle_signal(int signum, siginfo_t *info, void *context);
void	server(void);
// cl - clean up
void	freenull(void *pt);
void	exitcl(int code);
void	setfreept(t_data *data, void *pt);
void	freenullall(t_data *data);
void	freedatacmd(t_data *data);
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
void	gettkn(t_data *data, int i, int start);
void	loadcmdtkn(t_data *data);
// parsing
t_cmd	*parsepipe(t_data *data, int i);
_Bool	is_sym(char s);
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
