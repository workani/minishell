CC ?= cc
CC_FLAGS = -Iinclude -Wall -Wextra -Werror 
RM := rm -f

LIBFT := libft
LIBFT_ARCHIVE := $(LIBFT)/libft.a

NAME = minishell

SRC_DIR = src
ENV_DIR = $(SRC_DIR)/env
BUILTINS_DIR = $(SRC_DIR)/builtins

LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
EXECUTOR_DIR = $(SRC_DIR)/executor
REDIRECTIONS_DIR = $(SRC_DIR)/redirections

OBJS_DIR = obj

SRCS = $(SRC_DIR)/minishell.c $(SRC_DIR)/utils.c \
	   $(ENV_DIR)/env_lst.c \
	   $(LEXER_DIR)/lexer.c $(LEXER_DIR)/lexer_utils.c $(LEXER_DIR)/token.c \
	   $(PARSER_DIR)/parser.c $(PARSER_DIR)/parser_utils.c $(PARSER_DIR)/ast_utils.c \
	   $(EXECUTOR_DIR)/executor.c $(EXECUTOR_DIR)/executor_utils.c \
	   $(REDIRECTIONS_DIR)/redirections.c $(REDIRECTIONS_DIR)/redirection_ops.c \
	   $(BUILTINS_DIR)/echo.c $(BUILTINS_DIR)/env.c $(BUILTINS_DIR)/exit.c \
	   $(BUILTINS_DIR)/pwd.c  $(BUILTINS_DIR)/builtins_utils.c $(BUILTINS_DIR)/unset.c $(BUILTINS_DIR)/export.c


OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

vpath %.c $(SRC_DIR) $(ENV_DIR) $(BUILTINS_DIR) $(LEXER_DIR) $(PARSER_DIR) $(EXECUTOR_DIR) $(REDIRECTIONS_DIR)

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
