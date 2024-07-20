NAME	=	minishell

SRC_DIR	=	src
OBJ_DIR	=	obj
LIBFT	=	incs/libft/libft.a
SRCS	=	$(addprefix $(SRC_DIR)/tokenizing/, checks.c tkn_helpers.c tkns.c) \
			$(addprefix $(SRC_DIR)/parsing/, cmds.c expnd_help.c parse_help.c \
				expnd.c parse.c) \
			$(addprefix $(SRC_DIR)/, utils.c main.c)
OBJ		=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

INCS	=	-I incs/parse.h -I incs/libft/incs
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

GREY_BG	= \033[48;5;8m
GREY_T	= \33[90m
BLACK_T	= \33[30m
WHITE_T	= \033[97m
RESET 	= \033[0m

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				@mkdir -p $(dir $@)
				@$(CC) $(FLAGS) $(INCS) -c $< -o $@
				 @echo "$(GREY_T)Compiled $< into $@$(RESET)"

all:	$(NAME)

$(NAME):	$(OBJ)
			@make -C incs/libft -s
			@$(CC) $(OBJ) $(LIBFT) -o $(NAME)
			@echo "$(GREY_BG)$(WHITE_T)$(NAME) built successfully$(RESET)"


clean:
			@$(RM) $(OBJ)
			@$(RM) -r $(OBJ_DIR)
			@make clean -C incs/libft -s 
			@echo "$(GREY_BG)$(BLACK_T)*.o files & obj dir removed$(RESET)"

fclean:		clean
			@$(RM) $(NAME)
			@make fclean -C incs/libft -s
			@echo "$(GREY_BG)$(BLACK_T)all build artifacts removed$(RESET)"

re:			fclean all

.PHONY:	all clean fclean re
