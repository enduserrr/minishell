NAME	=	minishell

SRC_DIR	=	src
OBJ_DIR	=	obj
LIBFT	=	libft
SRCS	=	$(addprefix $(SRC_DIR)/parsing/tokens/, checks.c tkn_helpers.c tkns.c) \
			$(addprefix $(SRC_DIR)/parsing/parse/, cmds.c expnd_help.c parse_help.c \
				expnd.c parse.c) \
			$(addprefix $(SRC_DIR)/parsing/, utils.c main.c)
OBJ		=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

INCS	=	-I incs/tokens.h
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

$(OBJ_DIR)/%.o :	$(SRC_DIR)/%.c
				@mkdir -p $(dir $@)
				@$(CC) $(FLAGS) $(INCS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJ)
			@make -C libft
			@$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_DIR)
	@make clean -C $(LIBFT)

fclean:		clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT)

re:			fclean all

.PHONY:	all clean fclean re
