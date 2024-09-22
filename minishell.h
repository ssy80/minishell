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

/*typedef struct s_cmd
{
	int type;
}	t_cmd;*/

typedef struct s_execcmd {
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
}	t_execcmd;

/*typedef struct s_redircmd {
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
}	t_pipecmd;*/

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
	char	**envc;
	char	*buf;
	void	*freept[PTMAX];
	int		ptno;
	int		tkn[MAXLEN][2];
	int		itr;
	char	*cmd[MAXLEN];
	int		tkn_no;
}	t_data;

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

int	addenvvar(char *var, t_data *data);

// init
void	initfd(char *dir);
void	initdata(char buf[MAXLEN], char **env, t_data *data);
// shell
void	getprompt(char *dir);
void	gettkn(t_data *data, int i, int start);
void	loadcmdtkn(t_data *data);
// parsing
t_cmd	*parsepipe(t_data *data, int i);
bool	is_sym(char s);
int		parsechar(t_data *data, int i, int start);
int		parsesym(t_data *data, int i, int start);
int		parsespace(t_data *data, int i, int start);
bool	syn_check(t_data *data);
//lexer/parser/executor
//t_list *process_raw_input(char *str);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
//void    print_token_list(t_list *token_list);
//void parse_token_list(t_list **token_list);
//int equals(char *s1, char *s2);
void	lstremove_last(t_list **lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
//void    execute_list(t_list *token_list);
//char *do_other(t_list *cmd_list, char **child_args);
char	*ft_strjoin(char const *s1, char const *s2);

void print_inout_list(t_list *inout_list);
void print_args(char **args);
void print_cmd(t_list *cmd_list);
t_cmd *create_cmd(char *command, char **args, t_list *inout_list);
t_inout *create_inout(int type, char *file, char *heredoc, char *delimiter);

int is_inout(char *token);
int	get_args_len(char **args);
char **add_arg(char **args, char *arg);
char **get_null_args();
t_list *create_cmd_list(t_data *data);

int process_cmd_list(t_list *cmd_list, t_data *data);
char *get_command_path(char *cmd, t_data *data);
char **form_args(char *command, char **args);
int **get_pipe(int size);
int do_heredoc(t_inout *inout, int i);
int equals(char *s1, char *s2);
pid_t *get_pidt(int size);

char	*ft_itoa(int n_);

void free_cmd_cmd(char *cmd);
void free_cmd_args(char **args);
void free_cmdlist(t_list *cmd_list);
void free_inoutlist(t_list *inout_list);
void free_inout(t_inout *inout);
void free_cmd(t_cmd *cmd);
void	free_datacmd(t_data *data);

void free_pidt(pid_t *pidt);
void free_pipefd_all(int **pipefd, int size);
void free_charchar_str(char **str);

char	*ft_strdup(const char *s);

void	ft_freelist(t_list *lst);

int is_dir(char *command);

int is_builtin_fn(char *cmd);

void builtin_get_env(t_data *data);
int builtin_export(char **args, t_data *data);

char	*ft_substr(char const *s, unsigned int start_, size_t len);

int builtin_unset(char **args, t_data *data);

void unlink_file(char *filepath);

int is_spaces(char *str);

void builtin_exit();

int builtin_cd(char **args, t_data *data);

void builtin_echo(char **args);

char **get_current_env(t_data *data);

#endif
