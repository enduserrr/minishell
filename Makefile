
NAME	=	minishell

SRC_DIR	=	src
OBJ_DIR	=	obj
LIBFT	=	libft/libft.a

SRCS	=	$(addprefix $(SRC_DIR)/builtin_cmd/, cd.c echo.c env.c export.c pwd.c unset.c) \
			$(addprefix $(SRC_DIR)/tokens/, cmds.c errors.c expand.c parse_help.c parse.c \
				tkn_eval.c tkn_help.c tk_split.c tkns.c utils.c) \
			$(addprefix $(SRC_DIR)/other/, env_list.c minishell.c update_pwds.c utils.c) \
			$(addprefix $(SRC_DIR)/, main.c)
OBJ		=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

INC		=	-I incs
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror -lreadline 
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
			@make clean -C libft

fclean:		clean
			@$(RM) $(NAME)
			@make fclean -C libft

re:			fclean all

.PHONY	all clean fclean re