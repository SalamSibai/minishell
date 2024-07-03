# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 17:03:04 by mohammoh          #+#    #+#              #
#    Updated: 2024/07/03 19:09:30 by mohammoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_is/ft_isalnum.c \
		ft_is/ft_isalpha.c \
		ft_is/ft_isascii.c \
		ft_is/ft_isdigit.c \
		ft_is/ft_isprint.c \
		ft_is/ft_isspace.c \
		ft_is/ft_tolower.c \
		ft_is/ft_toupper.c \
		ft_list/ft_lstadd_back.c \
		ft_list/ft_lstadd_front.c \
		ft_list/ft_lstclear.c \
		ft_list/ft_lstdelone.c \
		ft_list/ft_lstiter.c \
		ft_list/ft_lstlast.c \
		ft_list/ft_lstmap.c \
		ft_list/ft_lstnew.c \
		ft_list/ft_lstsize.c \
		ft_mem/ft_memchr.c \
		ft_mem/ft_memcmp.c \
		ft_mem/ft_memcpy.c \
		ft_mem/ft_memdel.c \
		ft_mem/ft_memmove.c \
		ft_mem/ft_memset.c \
		ft_put/ft_putchar_fd.c \
		ft_put/ft_putendl_fd.c \
		ft_put/ft_putnbr_fd.c \
		ft_put/ft_putstr_fd.c \
		ft_str/ft_split.c \
		ft_str/ft_strcat.c \
		ft_str/ft_strchr.c \
		ft_str/ft_strcmp.c \
		ft_str/ft_strcpy.c \
		ft_str/ft_strdup.c \
		ft_str/ft_striteri.c \
		ft_str/ft_strjoin.c \
		ft_str/ft_strjoin_free.c \
		ft_str/ft_strlcat.c \
		ft_str/ft_strlcpy.c \
		ft_str/ft_strlen.c \
		ft_str/ft_strmapi.c \
		ft_str/ft_strncmp.c \
		ft_str/ft_strndup.c \
		ft_str/ft_strnstr.c \
		ft_str/ft_strrchr.c \
		ft_str/ft_strtrim.c \
		ft_str/ft_substr.c \
		ft_utils/ft_atoi.c \
		ft_utils/ft_bzero.c \
		ft_utils/ft_calloc.c \
		ft_utils/ft_free2d.c \
		ft_utils/ft_free.c \
		ft_utils/ft_itoa.c \
		ft_utils/ft_strjoin_gnl.c \
		ft_utils/get_next_line.c \
		ft_utils/get_next_line_bonus.c \

OBJECTS = $(SRC:.c=.o) 

HEAD	= ./
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(OBJECTS): %.o: %.c
	@$(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@

$(NAME): $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)
	echo "libft compiled"

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)
	echo "compilation removed"

re: fclean all

.PHONY: all clean fclean re