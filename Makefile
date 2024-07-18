NAME	=	minishell

SRC_DIR	=	src
OBJ_DIR	=	obj
LIBFT	=	incs/libft/libft.a
SRCS	=	$(addprefix $(SRC_DIR)/tokns/, checks.c tkn_helpers.c tkns.c) \
			$(addprefix $(SRC_DIR)/parsing/, cmds.c expnd_help.c parse_help.c \
				expnd.c parse.c) \
			$(addprefix $(SRC_DIR)/, utils.c main.c)
OBJ		=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

INCS	=	-I incs/tokens.h -I incs/libft/incs
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				@mkdir -p $(dir $@)
				@$(CC) $(FLAGS) $(INCS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJ)
			@make -C incs/libft
			@$(CC) $(OBJ) $(LIBFT) -o $(NAME)

clean:
			$(RM) $(OBJ)
			$(RM) -r $(OBJ_DIR)
			@make clean -C incs/libft

fclean:		clean
			@$(RM) $(NAME)
			@make fclean -C incs/libft

re:			fclean all

.PHONY:	all clean fclean re
