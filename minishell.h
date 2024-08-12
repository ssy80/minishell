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

typedef struct s_data
{
	char	**env;
	char	*buf;
	void	*freept[PTMAX];
	int		ptno;
}	t_data;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
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
void	getmyenv(char **envp);
void	exitcommand(char *input, t_data *data);
void	getcd(char *buf);
int		builtin_func(char *buf, t_data *data);
// init
void	initfd(char *dir);
void	initdata(char buf[MAXLEN], char **env, t_data *data);
// shell
void	getprompt(char *dir);

#endif
