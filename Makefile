DIR_BUILTIN			= ./builtin
DIR_CLEANUP			= ./cleanup
DIR_EXECUTOR		= ./executor
DIR_FT				= ./ft
DIR_PARSING			= ./parsing
DIR_HELPER			= ./helper
DIR					= .

SRC			= ${DIR}/minishell.c \
			  ${DIR_BUILTIN}/b_func.c \
			  ${DIR_BUILTIN}/b_func2.c \
			  ${DIR_BUILTIN}/builtin_cd_helper.c \
			  ${DIR_BUILTIN}/builtin_cd.c \
			  ${DIR_BUILTIN}/builtin_echo.c \
			  ${DIR_BUILTIN}/builtin_env.c \
			  ${DIR_BUILTIN}/builtin_exit.c \
			  ${DIR_BUILTIN}/builtin_export_helper.c \
			  ${DIR_BUILTIN}/builtin_export.c \
			  ${DIR_BUILTIN}/builtin_pwd.c \
			  ${DIR_BUILTIN}/builtin_unset.c \
			  ${DIR_BUILTIN}/builtin.c \
			  ${DIR_BUILTIN}/environment.c \
			  ${DIR_CLEANUP}/cl_clean_up.c \
			  ${DIR_CLEANUP}/util_free.c \
			  ${DIR_CLEANUP}/util_free2.c \
			  ${DIR_CLEANUP}/util_free3.c \
			  ${DIR_EXECUTOR}/create_cmd_list_helper.c \
			  ${DIR_EXECUTOR}/create_cmd_list_helper2.c \
			  ${DIR_EXECUTOR}/create_cmd_list_helper3.c \
			  ${DIR_EXECUTOR}/create_cmd_list_helper4.c \
			  ${DIR_EXECUTOR}/create_cmd_list.c \
			  ${DIR_EXECUTOR}/do_builtin.c \
			  ${DIR_EXECUTOR}/do_command_first.c \
			  ${DIR_EXECUTOR}/do_command_helper.c \
			  ${DIR_EXECUTOR}/do_command_helper2.c \
			  ${DIR_EXECUTOR}/do_command_last.c \
			  ${DIR_EXECUTOR}/do_command_mid.c \
			  ${DIR_EXECUTOR}/do_command.c \
			  ${DIR_EXECUTOR}/do_get_pidt.c \
			  ${DIR_EXECUTOR}/do_get_pipe.c \
			  ${DIR_EXECUTOR}/do_heredoc_helper.c \
			  ${DIR_EXECUTOR}/do_heredoc_helper2.c \
			  ${DIR_EXECUTOR}/do_heredoc_helper3.c \
			  ${DIR_EXECUTOR}/do_heredoc.c \
			  ${DIR_EXECUTOR}/do_inout.c \
			  ${DIR_EXECUTOR}/do_multiple_command.c \
			  ${DIR_EXECUTOR}/do_single_cmd.c \
			  ${DIR_EXECUTOR}/executor.c \
			  ${DIR_FT}/ft_atold.c \
			  ${DIR_FT}/ft_atoll.c \
			  ${DIR_FT}/ft_bzero.c \
			  ${DIR_FT}/ft_calloc.c \
			  ${DIR_FT}/ft_isalnum.c \
			  ${DIR_FT}/ft_isalpha.c \
			  ${DIR_FT}/ft_isdigit.c \
			  ${DIR_FT}/ft_itoa.c \
			  ${DIR_FT}/ft_lstadd_back_bonus.c \
			  ${DIR_FT}/ft_lstadd_front.c \
			  ${DIR_FT}/ft_lstclear_bonus.c \
			  ${DIR_FT}/ft_lstdelone.c \
			  ${DIR_FT}/ft_lstlast.c \
			  ${DIR_FT}/ft_lstnew_bonus.c \
			  ${DIR_FT}/ft_lstsize.c \
			  ${DIR_FT}/ft_putstr_fd.c \
			  ${DIR_FT}/ft_split.c \
			  ${DIR_FT}/ft_strchr.c \
			  ${DIR_FT}/ft_strdup.c \
			  ${DIR_FT}/ft_strjoin.c \
			  ${DIR_FT}/ft_strlcpy.c \
			  ${DIR_FT}/ft_strlen.c \
			  ${DIR_FT}/ft_strncmp.c \
			  ${DIR_FT}/ft_substr.c \
			  ${DIR_PARSING}/par_expand.c \
			  ${DIR_PARSING}/par_expand2.c \
			  ${DIR_PARSING}/par_expand3.c \
			  ${DIR_PARSING}/par_expand4.c \
			  ${DIR_PARSING}/par_expand5.c \
			  ${DIR_PARSING}/par_expanddollar.c \
			  ${DIR_PARSING}/par_get_token.c \
			  ${DIR_PARSING}/par_get_token2.c \
			  ${DIR_PARSING}/par_get_token3.c \
			  ${DIR_PARSING}/par_q_heredoc.c \
			  ${DIR_PARSING}/par_syntax.c \
			  ${DIR_PARSING}/par_tree.c \
			  ${DIR_HELPER}/init_data.c \
			  ${DIR_HELPER}/init_initfd.c \
			  ${DIR_HELPER}/is_spaces.c \
			  ${DIR_HELPER}/minishell_helper.c \
			  ${DIR_HELPER}/sig_signal.c \
			  ${DIR_HELPER}/sig_signal2.c \
			  ${DIR_HELPER}/util_common.c \

NAME 		= minishell
INCLUDE		= ./header
CC 			= cc
CFLAGS 		= -g -Wall -Wextra -Werror -I .
RFLAG 		= -lreadline
RM 			= rm -f
OBJS		= $(SRC:.c=.o)
HEADER      = ${INCLUDE}/minishell.h

%.o: %.c   $(HEADER)
			$(CC) $(CFLAGS) -c -I $(INCLUDE)  $< -o $(<:.c=.o)

#DIR_HELPER = ./helper
#SRC = $(NAME).c
#OBJ = $(SRC:.c=.o)
#HELPER = $(wildcard $(DIR_HELPER)/*.c)
# HELPER = $(DIR_HELPER)/ft_atoi.c \
#HELPER_OBJ = $(HELPER:.c=.o)
#$(NAME) : $(OBJS)
#	$(CC) $(CFLAGS) $^ -o $@ $(RFLAG) -c -I ${INCLUDE}
#$(DIR_HELPER)/%.o : $(DIR_HELPER)/%.c $(NAME).h
#	$(CC) -c $(CFLAGS) $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
		 $(CC) -g -o $(NAME) $(OBJS) $(RFLAG)

clean :
	     $(RM) $(OBJS)

fclean : clean
	     $(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re