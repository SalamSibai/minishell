# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 11:41:44 by mohammoh          #+#    #+#              #
#    Updated: 2024/06/03 13:28:46 by mohammoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			= minishell

VALIDATE_DIR	= ./validate
PARSE_DIR		= ./parsing
ENV_DIR			= ./env
EXPANSION_DIR	= ./expansion
DEBUG_DIR		= ./debug
OBJ_DIR			= ./obj

SRC	=	${PARSE_DIR}/parse_utils.c \
		${PARSE_DIR}/init_parsing.c \
		${PARSE_DIR}/set_tokens.c \
		${PARSE_DIR}/set_cmds.c \
		${PARSE_DIR}/initialization.c \
		${PARSE_DIR}/count_cmds.c \
		${ENV_DIR}/env_init.c\
		${ENV_DIR}/get_path.c\
		${EXPANSION_DIR}/expansion.c\
		${VALIDATE_DIR}/validate_id.c \
		${VALIDATE_DIR}/validate_input_redirection.c \
		${VALIDATE_DIR}/validate_output_redirection.c\
		${VALIDATE_DIR}/validate_pipe.c \
		${VALIDATE_DIR}/validate_syntax.c \
		${VALIDATE_DIR}/validate_utils.c \
		${VALIDATE_DIR}/validate_tokens.c \
		${VALIDATE_DIR}/validate_qoutes.c \
		${DEBUG_DIR}/print_data.c \
		./main.c \

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address 

RM = rm -rf

LIBFT = ./includes/libft/libft.a

HEAD = ./

CC = cc

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(PARSE_DIR) $(OBJ_DIR)/$(ENV_DIR) $(OBJ_DIR)/$(EXPANSION_DIR) $(OBJ_DIR)/$(VALIDATE_DIR) $(OBJ_DIR)/$(DEBUG_DIR)

$(LIBFT):
	$(MAKE) -C ./includes/libft

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@
	
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -Iincludes/minishell.h -o minishell

clean:
	$(MAKE) clean -C ./includes/libft
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C ./includes/libft
	$(RM) $(NAME)

re: fclean all

.phony:	all clean fclean re
