NAME = minishell
CC = cc
# CFLAGS = -g -Wall -Wextra -Werror -I .
CFLAGS = -g -Wall -Wextra -Werror -I .
RFLAG = -lreadline
RM = rm -f

DIR_HELPER = ./helper
SRC = $(NAME).c
OBJ = $(SRC:.c=.o)
HELPER = $(wildcard $(DIR_HELPER)/*.c)
# HELPER = $(DIR_HELPER)/ft_atoi.c \

HELPER_OBJ = $(HELPER:.c=.o)

all : $(NAME)

$(NAME) : $(HELPER_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(RFLAG)

$(DIR_HELPER)/%.o : $(DIR_HELPER)/%.c $(NAME).h
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	$(RM) $(HELPER_OBJ) $(OBJ)

fclean : clean
	$(RM) $(NAME) $(NAME_B) log.txt

re : fclean all

run : $(NAME)
	valgrind --leak-check=full ./$(NAME)

gdb: $(NAME)
	gdb ./$(NAME)
