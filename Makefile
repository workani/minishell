NAME = minishell

# Compiler and general flags
CC = cc
RM = rm -f

# --- ADD THIS SECTION FOR READLINE ---
# This is the standard path for readline installed with Homebrew on Apple Silicon
READLINE_PATH = /usr/local/opt/readline
# --- END OF NEW SECTION ---

# Compilation flags
# -I$(READLINE_PATH)/include tells the compiler where to find readline's .h files
CFLAGS = -Wall -Wextra -Werror -I$(READLINE_PATH)/include
INCLUDES = -Iinclude -I$(LIBFT)

# Libraries
LIBFT = libft
LIBFT_ARCHIVE = $(LIBFT)/libft.a
# -L$(READLINE_PATH)/lib tells the linker where to find the library file
# -lreadline tells the linker which library to link
LDFLAGS = -L$(READLINE_PATH)/lib -lreadline -lhistory

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source subdirectories
ENV_DIR = $(SRC_DIR)/env
BUILTINS_DIR = $(SRC_DIR)/builtins
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
EXECUTOR_DIR = $(SRC_DIR)/executor
REDIRECTIONS_DIR = $(SRC_DIR)/redirections

# Source files by category
MAIN_SRCS = minishell.c utils.c signals.c
ENV_SRCS = env_lst.c
BUILTINS_SRCS = echo.c env.c exit.c pwd.c cd.c export.c unset.c builtins_utils.c
LEXER_SRCS = lexer.c lexer_utils.c token.c
PARSER_SRCS = parser.c parser_utils.c ast_utils.c expander.c
EXECUTOR_SRCS = executor.c executor_utils.c
REDIRECTIONS_SRCS = redirections.c redirection_ops.c

# Combine all sources with their paths
SRCS = $(addprefix $(SRC_DIR)/, $(MAIN_SRCS)) \
       $(addprefix $(ENV_DIR)/, $(ENV_SRCS)) \
       $(addprefix $(BUILTINS_DIR)/, $(BUILTINS_SRCS)) \
       $(addprefix $(LEXER_DIR)/, $(LEXER_SRCS)) \
       $(addprefix $(PARSER_DIR)/, $(PARSER_SRCS)) \
       $(addprefix $(EXECUTOR_DIR)/, $(EXECUTOR_SRCS)) \
       $(addprefix $(REDIRECTIONS_DIR)/, $(REDIRECTIONS_SRCS))

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Header files
HEADERS = $(INC_DIR)/minishell.h $(INC_DIR)/types.h $(INC_DIR)/defines.h

# Colors for output
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(LIBFT_ARCHIVE) $(NAME)

$(NAME): $(OBJS) $(LIBFT_ARCHIVE)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBFT_ARCHIVE) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

$(LIBFT_ARCHIVE):
	@$(MAKE) -C $(LIBFT) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) Makefile | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/env $(OBJ_DIR)/builtins $(OBJ_DIR)/lexer \
	$(OBJ_DIR)/parser $(OBJ_DIR)/executor $(OBJ_DIR)/redirections

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean --no-print-directory

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean --no-print-directory

re: fclean all

bonus: all

norm:
	@norminette $(SRCS) $(HEADERS)

.PHONY: all clean fclean re bonus norm



# CC ?= cc
# CC_FLAGS = -Iinclude -Wall -Wextra -Werror 
# RM := rm -f

# LIBFT := libft
# LIBFT_ARCHIVE := $(LIBFT)/libft.a

# NAME = minishell

# SRC_DIR = src
# ENV_DIR = $(SRC_DIR)/env
# BUILTINS_DIR = $(SRC_DIR)/builtins

# LEXER_DIR = $(SRC_DIR)/lexer
# PARSER_DIR = $(SRC_DIR)/parser
# EXECUTOR_DIR = $(SRC_DIR)/executor
# REDIRECTIONS_DIR = $(SRC_DIR)/redirections

# OBJS_DIR = obj

# SRCS = $(SRC_DIR)/minishell.c $(SRC_DIR)/utils.c \
# 	   $(ENV_DIR)/env_lst.c \
# 	   $(LEXER_DIR)/lexer.c $(LEXER_DIR)/lexer_utils.c $(LEXER_DIR)/token.c \
# 	   $(PARSER_DIR)/parser.c $(PARSER_DIR)/parser_utils.c $(PARSER_DIR)/ast_utils.c \
# 	   $(EXECUTOR_DIR)/executor.c $(EXECUTOR_DIR)/executor_utils.c \
# 	   $(REDIRECTIONS_DIR)/redirections.c $(REDIRECTIONS_DIR)/redirection_ops.c \
# 	   $(BUILTINS_DIR)/echo.c $(BUILTINS_DIR)/env.c $(BUILTINS_DIR)/exit.c \
# 	   $(BUILTINS_DIR)/pwd.c  $(BUILTINS_DIR)/builtins_utils.c $(BUILTINS_DIR)/unset.c $(BUILTINS_DIR)/export.c


# OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

# vpath %.c $(SRC_DIR) $(ENV_DIR) $(BUILTINS_DIR) $(LEXER_DIR) $(PARSER_DIR) $(EXECUTOR_DIR) $(REDIRECTIONS_DIR)

# $(OBJS_DIR)/%.o: %.c
# 	mkdir -p $(OBJS_DIR)
# 	$(CC) $(CC_FLAGS) -c $< -o $@ 

# $(NAME): $(OBJS) $(LIBFT_ARCHIVE)
# 	$(CC) $(CC_FLAGS) $(OBJS) -lreadline -lhistory libft/libft.a \
# 	 -o $(NAME)

# all: $(NAME)

# $(LIBFT_ARCHIVE): 
# 	@make -C $(LIBFT)

# clean: 
# 	@make clean -C $(LIBFT)
# 	$(RM) $(OBJS)

# fclean: clean
# 	@make fclean -C $(LIBFT)
# 	$(RM) $(NAME)

# re: fclean all


# .PHONY: all clean fclean re $(LIBFT_ARCHIVE)
