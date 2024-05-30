# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 11:41:44 by mohammoh          #+#    #+#              #
#    Updated: 2024/05/30 18:46:55 by mohammoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC = ./parsing/parse_utils.c ./parsing/init_parsing.c ./env/env_init.c ./env/get_path.c \
		./parsing/set_tokens.c \
		./validate/validate_syntax.c ./validate/validate_utils.c validate/validate_tokens.c\
		./main.c \

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address 

RM = rm -rf

LIBFT = ./includes/libft/libft.a

HEAD = ./

CC = cc


OBJ = $(SRC:%.c=%.o)


all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./includes/libft
	
$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@
	
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -Iincludes/minishell.h -o minishell

clean:
	$(MAKE) clean -C ./includes/libft
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C ./includes/libft
	$(RM) $(NAME)

re: fclean all

.phony:	all clean fclean re