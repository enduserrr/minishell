
NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror -lreadline

SRCS = 	main.c \
		srcs/minishell.c \
		srcs/utils.c \
		builtin/cd_cmd.c \
		builtin/env_cmd.c \
		builtin/exit_cmd.c \
		builtin/echo_cmd.c \
		builtin/pwd_cmd.c

OBJ = $(SRCS:.c=.o)

LIBFT = libft/libft.a

$(NAME): $(OBJ)
	@cd libft && make
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean : 
	rm -f $(OBJ)

all: $(NAME)