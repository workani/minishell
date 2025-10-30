# ────────────────────────────
#  Project-wide settings
# ────────────────────────────
NAME            := minishell
CC              ?= cc
RM              := rm -f
MAKE_SILENT     := --no-print-directory

# ────────────────────────────
#  ANSI colours & emojis
# ────────────────────────────
GREEN   := \033[1;92m   # bright green
YELLOW  := \033[1;93m   # bright yellow
RED     := \033[1;91m   # bright red
BLUE    := \033[1;94m   # bright blue
MAGENTA := \033[1;95m   # bright magenta
CYAN    := \033[1;96m   # bright cyan
RESET   := \033[0m

# ────────────────────────────
#  Directories
# ────────────────────────────
SRC_DIR         := src
OBJ_DIR         := obj
INC_DIR         := include

ENV_DIR         := $(SRC_DIR)/env
BUILTINS_DIR    := $(SRC_DIR)/builtins
LEXER_DIR       := $(SRC_DIR)/lexer
PARSER_DIR      := $(SRC_DIR)/parser
EXECUTOR_DIR    := $(SRC_DIR)/executor
REDIRECTIONS_DIR:= $(SRC_DIR)/redirections

# ────────────────────────────
#  Third-party libraries
# ────────────────────────────
LIBFT           := libft
LIBFT_ARCHIVE   := $(LIBFT)/libft.a

# Homebrew users can override this when invoking make
READLINE_PATH   ?= /usr/local/opt/readline

# ────────────────────────────
#  Compiler & linker flags
# ────────────────────────────
CFLAGS  := -Wall -Wextra -Werror -I$(INC_DIR) -I$(READLINE_PATH)/include
LDFLAGS := -L$(READLINE_PATH)/lib -lreadline -lhistory

# ────────────────────────────
#  Source files
# ────────────────────────────
MAIN_SRCS        := minishell.c utils.c signals.c
ENV_SRCS         := env_lst.c env_lst_utils.c
BUILTINS_SRCS    := builtins.c echo.c env.c exit.c pwd.c cd.c export.c unset.c builtins_utils.c
LEXER_SRCS       := lexer.c lexer_utils.c token.c
PARSER_SRCS      := parser.c parser_utils.c ast_utils.c expander.c expander_utils.c
EXECUTOR_SRCS    := executor.c executor_utils.c get_cmd.c
REDIRECTIONS_SRCS:= redirections.c redirection_ops.c

SRCS := \
  $(addprefix $(SRC_DIR)/,$(MAIN_SRCS)) \
  $(addprefix $(ENV_DIR)/,$(ENV_SRCS)) \
  $(addprefix $(BUILTINS_DIR)/,$(BUILTINS_SRCS)) \
  $(addprefix $(LEXER_DIR)/,$(LEXER_SRCS)) \
  $(addprefix $(PARSER_DIR)/,$(PARSER_SRCS)) \
  $(addprefix $(EXECUTOR_DIR)/,$(EXECUTOR_SRCS)) \
  $(addprefix $(REDIRECTIONS_DIR)/,$(REDIRECTIONS_SRCS))

OBJS    := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
HEADERS := $(INC_DIR)/minishell.h $(INC_DIR)/types.h $(INC_DIR)/defines.h

# ────────────────────────────
#  Primary targets
# ────────────────────────────
all: $(NAME)

$(NAME): $(LIBFT_ARCHIVE) $(OBJS)
	@echo "$(MAGENTA)🔗  Linking $@...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_ARCHIVE) $(LDFLAGS) -o $@
	@echo "$(GREEN)✅  Build succeeded$(RESET)"

# Build libft silently
$(LIBFT_ARCHIVE):
	@$(MAKE) -C $(LIBFT) $(MAKE_SILENT)

# Compile every .c → .o, mirroring source tree inside obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(BLUE)🔧  Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Ensure obj directory root exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# ────────────────────────────
#  House-keeping targets
# ────────────────────────────
clean:
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean $(MAKE_SILENT)
	@echo "$(RED)🗑  Object files removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean $(MAKE_SILENT)
	@echo "$(RED)🗑  Executable removed$(RESET)"

re: fclean all

norm:
	@echo "$(CYAN)🔍  Running norminette...$(RESET)"
	@norminette $(SRCS) $(HEADERS)

.PHONY: all clean fclean re norm
