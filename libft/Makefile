# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfreire- <pfreire-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 16:26:27 by pfreire-          #+#    #+#              #
#    Updated: 2026/05/21 16:07:44 by pfreire-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Werror -Wextra -g
# SRCSFILES = $(shell find . -name srcs.txt)
# SRCS = $(foreach f,$(SRCSFILES),$(shell awk 'NR==1{path=$$0; next} {print path"/"$$0}' $(f)))
SRCS = ctype/ft_isalnum.c \
ctype/ft_isalpha.c \
ctype/ft_isascii.c \
ctype/ft_isdigit.c \
ctype/ft_isprint.c \
ctype/ft_tolower.c \
ctype/ft_toupper.c \
ctype/ft_iscntrl.c \
ctype/ft_isspace.c \
ctype/ft_isblank.c \
ctype/ft_isgraph.c \
ctype/ft_islower.c \
ctype/ft_ispunct.c \
ctype/ft_isupper.c \
gnl/get_next_line.c \
gnl/get_next_line_utils.c \
ints/randomizer.c \
memory/arr_size.c \
memory/free_2d.c \
memory/free_3d.c \
memory/ft_bzero.c \
memory/ft_calloc.c \
memory/ft_memchr.c \
memory/ft_memcmp.c \
memory/ft_memcpy.c \
memory/ft_memmove.c \
memory/ft_memset.c \
output/ft_printhex.c \
output/ft_putchar.c \
output/ft_putchar_fd.c \
output/ft_putendl_fd.c \
output/ft_putnbr.c \
output/ft_putnbr_fd.c \
output/ft_putnbr_hex.c \
output/ft_putnbr_hexlow.c \
output/ft_putstr.c \
output/ft_putstr_fd.c \
output/ft_putunbr.c \
print/dprintf/ft_dprintf.c \
print/dprintf/ft_dprinthex.c \
print/dprintf/ft_dputchar.c \
print/dprintf/ft_dputnbr.c \
print/dprintf/ft_dputnbr_hex.c \
print/dprintf/ft_dputnbr_hexlow.c \
print/dprintf/ft_dputstr.c \
print/dprintf/ft_dputunbr.c \
print/printf/ft_printf.c \
print/printf/ft_printlhex.c \
print/printf/ft_putlchar.c \
print/printf/ft_putlnbr.c \
print/printf/ft_putlnbr_hex.c \
print/printf/ft_putlnbr_hexlow.c \
print/printf/ft_putlstr.c \
print/printf/ft_putlunbr.c \
strings/ft_atoi.c \
strings/ft_count_words.c \
strings/ft_itoa.c \
strings/ft_split.c \
strings/ft_strchr.c \
strings/ft_strcmp.c \
strings/ft_strcpy.c \
strings/ft_strdup.c \
strings/ft_striteri.c \
strings/ft_strjoin.c \
strings/ft_strlcat.c \
strings/ft_strlcpy.c \
strings/ft_strlen.c \
strings/ft_strmapi.c \
strings/ft_strncmp.c \
strings/ft_strnstr.c \
strings/ft_strrchr.c \
strings/ft_strtrim.c \
strings/ft_substr.c \
strings/ft_wordcpy.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS): %.o: %.c
	cc $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)
	rm -f $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
