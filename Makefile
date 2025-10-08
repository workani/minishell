CC ?= cc
CC_FLAGS = -Wall -Wextra -Werror -Iinclude
RM := rm -f

LIBFT := libft
LIBFT_ARCHIVE := $(LIBFT)/libft.a

NAME = minishell

SRC_DIR = src
ENV_DIR = $(SRC_DIR)/env
BUILTINS_DIR = $(SRC_DIR)/builtins

LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser

OBJS_DIR = obj

SRCS = $(ENV_DIR)/env_lst.c $(SRC_DIR)/utils.c $(SRC_DIR)/minishell.c \
	   $(BUILTINS_DIR)/pwd.c \
	   $(LEXER_DIR)/lexer_utils.c $(LEXER_DIR)/lexer.c $(LEXER_DIR)/token.c \
	   $(PARSER_DIR)/ast.c $(PARSER_DIR)/parser_utils.c $(PARSER_DIR)/parser.c


OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

vpath %.c $(SRC_DIR) $(ENV_DIR) $(BUILTINS_DIR) $(LEXER_DIR) $(PARSER_DIR)

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CC_FLAGS) -c $< -o $@ 

$(NAME): $(OBJS) $(LIBFT_ARCHIVE)
	$(CC) $(CC_FLAGS) $(OBJS) -lreadline -lhistory libft/libft.a \
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
