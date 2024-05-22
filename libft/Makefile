
OBJS_ORG = $(SRC_ORG:.c=.o)
SRC_ORG= $(addprefix $(SRC_DIR)/original/, \
ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
ft_strdup.c ft_striteri.c ft_strjoin.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
ft_substr.c ft_tolower.c ft_toupper.c )

OBJS_PRINTF = $(SRC_PRINTF:.c=.o)
SRC_PRINTF = $(addprefix $(SRC_DIR)/printf/, \
ft_printf.c functions_printf.c )

OBJS_GNL = $(SRC_GNL:.c=.o)
SRC_GNL = $(addprefix $(SRC_DIR)/gnl/, \
get_next_line.c get_next_line_utils.c )

SRC_DIR = .
CC = cc 
AR = ar 
FLAGS = -Wall -Wextra -Werror

LIBFT_NAME = libft.a
LIBFT_HEADER = libft.h


all : $(LIBFT_NAME)

$(LIBFT_NAME) : $(OBJS_ORG) $(OBJS_PRINTF) $(OBJS_GNL)
	@$(AR) -rcs $(LIBFT_NAME) $(OBJS_ORG) $(OBJS_PRINTF) $(OBJS_GNL)

clean : 
	@rm -f $(OBJS_ORG) $(OBJS_PRINTF) $(OBJS_GNL)

fclean : clean 
	@rm -f $(LIBFT_NAME)

re : fclean all

%.o : %.c $(LIBFT_HEADER)
	@/bin/echo -n .
	@$(CC) $(FLAGS) -c $< -o $@  -I $(SRC_DIR)

.PHONY: all clean fclean re