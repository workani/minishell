.PHONY: all clean fclean

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -O0
RM = rm -f

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	ft_calloc.c ft_strdup.c ft_toupper.c ft_tolower.c \
	ft_strchr.c ft_strncmp.c ft_strcmp.c ft_memchr.c ft_memcmp.c \
	ft_strnstr.c ft_atoi.c ft_atod.c ft_strrchr.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_strtoupper.c ft_printf.c putptr.c putstr.c puthex.c putuint.c

OBJS := $(SRCS:%.c=%.o)
NAME := libft.a

%.o: %.c
	$(CC) $(FLAGS) -c  -o $@ $<

$(NAME): $(OBJS)
	ar rcs $@ $^

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all
