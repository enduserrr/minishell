
NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror -lreadline

SRCS = 

OBJ = $(SRCS:.c=.o)

LIBFT = libft/libft.a

$(NAME): $(OBJ)
	@cd libft && make
	$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)

clean : 
	@rm -f $(OBJ)
	@cd libft && make clean

fclean : clean
	@rm -f $(NAME)
	@cd libft && make fclean

all: $(NAME)