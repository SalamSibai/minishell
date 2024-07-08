# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mohammoh <mohammoh@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/08 11:41:44 by mohammoh          #+#    #+#              #
#    Updated: 2024/07/07 05:47:34 by mohammoh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME			= minishell

VALIDATE_DIR	= ./validate
PARSE_DIR		= ./parsing
ENV_DIR			= ./env
EXPANSION_DIR	= ./expansion
DEBUG_DIR		= ./debug
OBJ_DIR			= ./obj
BUILTINS_DIR	= ./builtins
EXEC_DIR		= ./execution
FREE_DIR		= ./cleanup
REDIR_DIR		= ./redirections
SIG_DIR			= ./signals

SRC	=	${PARSE_DIR}/parse_utils.c \
		${PARSE_DIR}/init_parsing.c \
		${PARSE_DIR}/malloc_tokens.c \
		${PARSE_DIR}/set_tokens.c \
		${PARSE_DIR}/set_tokens_utils.c \
		${PARSE_DIR}/set_cmds.c \
		${PARSE_DIR}/set_cmds_utils.c \
		${PARSE_DIR}/initialization.c \
		${PARSE_DIR}/redir_utils.c \
		${ENV_DIR}/env_init.c\
		${ENV_DIR}/get_path.c\
		${ENV_DIR}/env_utils.c\
		${ENV_DIR}/env_sort.c\
		${ENV_DIR}/env_var_and_path.c\
		${EXPANSION_DIR}/expansion.c\
		${VALIDATE_DIR}/validate_id.c \
		${VALIDATE_DIR}/validate_input_redirection.c \
		${VALIDATE_DIR}/validate_output_redirection.c\
		${VALIDATE_DIR}/validate_pipe.c \
		${VALIDATE_DIR}/validate_syntax.c \
		${VALIDATE_DIR}/validate_utils.c \
		${VALIDATE_DIR}/validate_tokens.c \
		${VALIDATE_DIR}/validate_qoutes.c \
		${REDIR_DIR}/check_redirection.c\
		${REDIR_DIR}/get_input.c\
		${REDIR_DIR}/set_output.c\
		${REDIR_DIR}/redirect_fds.c\
		${REDIR_DIR}/redirect_inputs.c\
		${REDIR_DIR}/redirect_output.c\
		${REDIR_DIR}/pipes_utils.c\
		${REDIR_DIR}/redirect_utils.c\
		${BUILTINS_DIR}/cd.c \
		${BUILTINS_DIR}/echo.c \
		${BUILTINS_DIR}/env.c \
		${BUILTINS_DIR}/export.c \
		${BUILTINS_DIR}/pwd.c \
		${BUILTINS_DIR}/unset.c \
		${BUILTINS_DIR}/exit.c \
		${EXEC_DIR}/execution.c \
		${EXEC_DIR}/builtins.c \
		${EXEC_DIR}/exec_cmds.c \
		${EXEC_DIR}/execution_utils.c \
		${EXEC_DIR}/execution_utils2.c \
		${FREE_DIR}/free_data.c \
		${FREE_DIR}/close_fds.c \
		${FREE_DIR}/error_handler.c\
		${SIG_DIR}/termios.c \
		${DEBUG_DIR}/print_data.c \
		./main.c \

CFLAGS = -Wall -Werror -Wextra -g3

RM = rm -rf

LIBFT = ./includes/libft/libft.a

HEAD = ./

CC = cc

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(PARSE_DIR) $(OBJ_DIR)/$(ENV_DIR) $(OBJ_DIR)/$(EXPANSION_DIR) $(OBJ_DIR)/${REDIR_DIR} $(OBJ_DIR)/$(VALIDATE_DIR) $(OBJ_DIR)/${BUILTINS_DIR} $(OBJ_DIR)/${EXEC_DIR} $(OBJ_DIR)/${FREE_DIR} $(OBJ_DIR)/$(SIG_DIR) $(OBJ_DIR)/$(DEBUG_DIR)

$(LIBFT):
	$(MAKE) -C ./includes/libft

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -I/Users/mohammoh/Documents/Tools/homebrew/opt/readline/include -I $(HEAD) $< -o $@
	
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -L /Users/mohammoh/Documents/Tools/homebrew/opt/readline/lib -lreadline  -Iincludes/minishell.h -o minishell


clean:
	$(MAKE) clean -C ./includes/libft
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C ./includes/libft
	$(RM) $(NAME)

leak:
	valgrind --suppressions=readlineleak.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell
re: fclean all

.phony:	all clean fclean re leak

# valgrind --leak-check=full --show-leak-kinds=all ./minishell
# $(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
# 	$(CC) $(CFLAGS) -c -I/Users/mohammoh/Documents/Tools/homebrew/opt/readline/include -I $(HEAD) $< -o $@
	
# $(NAME): $(OBJ) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -L /Users/mohammoh/Documents/Tools/homebrew/opt/readline/lib -lreadline  -Iincludes/minishell.h -o minishell


# for my laptop
# $(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
# 	$(CC) $(CFLAGS) -c -I/home/linuxbrew/.linuxbrew/opt/readline/include -I $(HEAD) $< -o $@
	
# $(NAME): $(OBJ) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -L //home/linuxbrew/.linuxbrew/opt/readline/lib -lreadline  -Iincludes/minishell.h -o minishell
