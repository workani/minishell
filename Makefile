CC ?= cc
#CC_FLAGS = -Wall -Wextra -Werror -Iinclude
CC_FLAGS = -Iinclude
RM := rm -f

LIBFT := libft
LIBFT_ARCHIVE := $(LIBFT)/libft.a

NAME = nanoshell

SRC_DIR = src
ENV_DIR = $(SRC_DIR)/env

OBJS_DIR = obj

SRCS = $(ENV_DIR)/env_lst.c $(SRC_DIR)/utils.c $(SRC_DIR)/minishell.c

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

vpath %.c $(SRC_DIR) $(ENV_DIR)

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CC_FLAGS) -c $< -o $@ 

$(NAME): $(OBJS) $(LIBFT_ARCHIVE)
	$(CC) $(CC_FLAGS) $(OBJS) libft/libft.a \
	 -o $(NAME)

all: $(NAME)

$(LIBFT_ARCHIVE): 
	@make -C $(LIBFT)

clean: 
	@make clean -C $(LIBFT)
	$(RM) $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re $(LIBFT_ARCHIVE)
