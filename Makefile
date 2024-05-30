# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssibai < ssibai@student.42abudhabi.ae>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 11:41:44 by mohammoh          #+#    #+#              #
#    Updated: 2024/05/30 19:33:06 by ssibai           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			= minishell

VALIDATE_DIR	= ./validate
PARSE_DIR		= ./parsing
ENV_DIR			= ./env

SRC	=	${PARSE_DIR}/parse_utils.c \
		${PARSE_DIR}/init_parsing.c \

		${ENV_DIR}/env_init.c \
		${ENV_DIR}/get_path.c \

		${VALIDATE_DIR}/set_tokens.c \
		${VALIDATE_DIR}/validate_syntax.c \
		${VALIDATE_DIR}/validate_utils.c \
		${VALIDATE_DIR}/validate_id.c \
		${VALIDATE_DIR}/validate_pipe.c \
		${VALIDATE_DIR}/validate_input_redirection.c \
		${VALIDATE_DIR}/validate_output_redirection.c\

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