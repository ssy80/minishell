/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoong <yoong@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:49:50 by yoong             #+#    #+#             */
/*   Updated: 2024/10/16 15:01:48 by ssian            ###   ########.fr       */
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
# define MAXEXP 5000
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

typedef struct s_execcmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}	t_execcmd;

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

	t_list	*cmd_list;
	pid_t	*pidt;
	int		**pipefd;

}	t_data;

/*
	0=create(>), 1=append(>>), 2=infile(<), 3=heredoc(<<)
*/
typedef struct s_inout
{
	int		type;
	char	*file;
	char	*heredoc;
	char	*delimiter;
}	t_inout;

/* e.g cmd: ls -l -a | grep zz | wc > a
   break to 3 cmd 
   1) ls -l -a   (**args= {"-l", "-a", NULL})
   2) grep zz    (**args= {"zz", NULL})  
   3) wc > a     (**args=NULL, inout_list = 
   {t_inout={type=0;file="a";heredoc=NULL;delimiter=NULL},...,}
*/
typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	t_list	*inout_list;
}	t_cmd;

typedef struct s_ccmd
{
	t_list	*cmd_list;
	t_list	*inout_list;
	char	*command;
	char	**args;
}	t_ccmd;

typedef struct s_stack
{
	int		tail;
	char	line[MAXLEN];
}	t_stack;

typedef struct s_heredoc
{
	t_data	*data;
	char	*file;
	int		filefd;
	int		*pipefd;
	char	*delimiter;
}	t_heredoc;

// ft
int			ft_isalpha(int a);
int			ft_isalnum(int a);
void		ft_bzero(void *b, size_t len);
void		*ft_calloc(size_t number, size_t size);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		**ft_split(char const *s, char c);
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
void		ft_lstclear(t_list **lst, void (*del)(void*));
// signal
void		handle_signal(int signum, siginfo_t *info, void *context);
void		server(void);
void		set_signal_in_command(void);
// cl - clean up
void		freenull(void *pt);
void		exitcl(int code);
void		setfreept(t_data *data, void *pt);
void		freenullall(t_data *data);
void		freedatacmd(t_data *data);
// built in function
void		getmyenv(t_data *data);
char		*getenvvar(char *var, t_data *data);
bool		isvalidenvkey(char *var);
int			addenvvar(char *var, t_data *data);
void		lltoarray(t_data *data);
int			listlength(t_list *a);
void		exitcommand(char *input, t_data *data);
void		getpwd(void);
void		getcd(char *buf);
int			builtin_func(char *buf, t_data *data);
// init
void		initfd(char *dir);
void		initdata(char buf[MAXLEN], char **env, t_data *data);
// shell
void		getprompt(char *dir);
void		gettkn(t_data *data, int i, int start);
void		loadcmdtkn(t_data *data);
// parsing
int			parse1q(t_data *data, int i, int start);
int			parse2q(t_data *data, int i, int start);
int			parsechar(t_data *data, int i, int start);
int			parsesym(t_data *data, int i, int start);
int			parsenum(t_data *data, int i, int start);
void		setdatatkn(t_data *data, int i, int start);
void		gettkn(t_data *data, int i, int start);
void		loadcmdtkn(t_data *data);
bool		is_whitesp(char s);
bool		is_sym(char s);
int			parsespace(t_data *data, int i, int start);
bool		syn_check(t_data *data);
// expander
void		exp1q(char *s, int a[2], char *line, t_data *data);
void		exp_1s(char *s, int a[2], char *line);
void		exp_sq(int a[2], char *line, t_data *data);
void		exp_s(char *s, int a[2], char *line, t_data *data);
void		exp2q(char *s, int a[2], char *line, t_data *data);
void		exptkn(char *s, int a[2], char *line, t_data *data);
int			expander(char *s, t_data *data, int i);
bool		ignoreexp(char *s);
bool		ignoreexp2(char *s);
char		*expand1tkn(char *s, t_data *data);
void		clonetkn(char (*copy)[MAXLEN], t_data *data);
void		expandss(t_stack *stack, char *s, t_data *data);
void		qremoval(char *s, t_stack *stack);
void		jointkn(t_data *data);
void		retokenise(t_data *data);
void		expandswrapper(char *s, t_stack *stack);
// main
void		getprompt(char *dir);
int			getcmd(char *buf, int size, char *dir, t_data *data);
void		error_main(t_data *data);
void		free_main_last(t_list *cmd_list, t_data *data);
int			do_expander(t_data *data);
//executor
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
char		*ft_strjoin(char const *s1, char const *s2);
void		print_inout_list(t_list *inout_list);
void		print_args(char **args);
void		print_cmd(t_list *cmd_list);
t_cmd		*create_cmd(char *command, char **args, t_list *inout_list);
t_inout		*create_inout(int type, char *file, char *heredoc, char *delimiter);
int			is_inout(char *token);
int			get_args_len(char **args);
char		**add_arg(char **args, char *arg);
char		**get_null_args(void);
t_list		*create_cmd_list(t_data *data);
int			process_cmd_list(t_list *cmd_list, t_data *data);
int			**get_pipe(int size);
int			equals(char *s1, char *s2);
pid_t		*get_pidt(int size);
char		*ft_itoa(int n_);
void		free_cmd_cmd(char *cmd);
void		free_cmd_args(char **args);
void		free_cmdlist(t_list *cmd_list);
void		free_inoutlist(t_list *inout_list);
void		free_inout(t_inout *inout);
void		free_cmd(t_cmd *cmd);
void		free_datacmd(t_data *data);
void		free_pidt(pid_t *pidt);
void		free_pipefd_all(int **pipefd, int size);
void		free_charchar_str(char **str);
char		*ft_strdup(const char *s);
void		ft_freelist(t_list *lst);
int			is_dir(char *command);
int			is_builtin_fn(char *cmd);
int			builtin_get_env(char **args, t_data *data);
int			builtin_export(char **args, t_data *data);
char		*ft_substr(char const *s, unsigned int start_, size_t len);
void		builtin_unset(char **args, t_data *data);
int			is_spaces(char *str);
int			builtin_exit(char **args, t_data *data);
int			builtin_cd(char **args, t_data *data);
void		builtin_echo(char **args);
char		**get_current_env(t_data *data);
int			is_var_in_env(char *str, t_data *data);
int			replace_var_in_env(char *str, t_data *data);
void		builtin_pwd(void);
int			remove_var_in_env(char *start, t_data *data);
void		free_all(t_data *data);
int			update_exit_status(int status, t_data *data);
int			ft_isdigit(int c);
long long	ft_atoll(const char *str);
long double	ft_atold(const char *str);
int			add_inout(t_list **inout_list, int inout_type, char *inout_value);
int			add_cmd(char *command, char **args,
				t_list *inout_list, t_list **cmd_list);
void		print_error_create_cmdlist(void);
void		do_single_cmd(t_data *data);
int			do_is_inout(t_data *data, t_ccmd *ccmd, int *i);
void		do_inout(t_list *inout_list, t_data *data);
void		do_command(t_cmd *cmd, t_data *data);
void		do_command_first(t_cmd *cmd, int pipefd_out[],
				pid_t pidt, t_data *data);
int			do_builtin(t_cmd *cmd, t_data *data);
void		do_command_last(t_cmd *cmd, int pipefd_in[],
				pid_t pidt, t_data *data);
void		do_command_mid(t_cmd *cmd, int i, t_data *data);
void		do_multiple_command(t_list *cmd_list, int size, t_data *data);
void		error_command_is_dir(t_cmd *cmd, t_data *data);
void		error_no_command(t_cmd *cmd, t_data *data);
void		error_no_env(t_cmd *cmd, t_data *data);
char		*get_env_path(t_data *data);
void		error_no_home(void);
void		error_cd(t_data *data);
char		*get_pwd(void);
void		error_fork(t_data *data);
void		error_execve(t_cmd *cmd, t_data *data);
char		*get_tmp_file(int i);
void		handle_signal_in_command(int sig);
void		set_signal_in_command(void);
void		print_error_heredoc(void);
void		set_sigint_status(t_data *data);
void		free_all2(t_data *data);
void		error_no_file(t_cmd *cmd, t_data *data);
void		error_no_permission(t_cmd *cmd, t_data *data);
int			is_cmd_path(char *cmd);
int			check_x_permission(char *command);
int			check_got_file(char *command);
int			do_heredoc(t_list *cmd_list, t_data *data);
int			starts_with(char *str, char *start);
void		error_many_args_cd(void);
void		error_export(t_data *data);
int			is_contain(char *str, char c);
int			is_operator_in_quotes(char *str);
int			expand_str(int i, t_data *data);
int			is_contain_quotes(char *str);
void		warning_heredoc_eof(char *delimiter);
void		handle_sig_child(int sig);
void		cleanup_child(t_heredoc *heredoc);
void		write_line(int got_quotes, char *line,
				t_data *data, int filefd);
void		do_readline(char *delimiter, int filefd,
				int got_quotes, t_data *data);
char		*get_delimiter(char *inout_delimiter, int got_quotes);
void		close_free_heredoc(t_heredoc *heredoc);
void		save_heredoc_file(int pipefd[2], t_inout *inout);
#endif
