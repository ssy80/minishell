DIR			= .
SRC			= ${DIR}/test_executor.c \
			  ${DIR}/executor.c \
			  ${DIR}/executor_helper.c 
			 

OBJS		= ${SRC:.c=.o}

INCLUDE		= ./header

NAME	    = minishell

AR			= ar rcs

CC			= cc -Wall -Wextra -Werror

LIBFT_DIR	= ./libft

LIBFT			= ${LIBFT_DIR}/libft.a

all: ${NAME}

%.o: %.c
	${CC} -c -I ${INCLUDE}  $< -o ${<:.c=.o}

${NAME}: ${OBJS} ${LIBFT}
	cc -g -o ${NAME} ${OBJS} ${LIBFT} -lreadline

${LIBFT}:
		make bonus -C ${LIBFT_DIR}

clean:
	make clean -C ${LIBFT_DIR}
	rm -f ${OBJS}

fclean: clean
	make fclean -C ${LIBFT_DIR}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
