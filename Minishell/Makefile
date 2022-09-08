
NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/usr/local/opt/readline/include #-fsanitize=address -g3
LDFLAGS = -L/usr/include -L/usr/local/opt/readline/lib -lreadline
RM = rm -f

MAIN = srcs/ms_main_bonus.c

# SRC = minishell.c

# BLTIN = builtin/echo.c builtin/builtin.c builtin/export.c builtin/export_utils.c \
# 		builtin/env.c builtin/unset.c builtin/unset_utils.c builtin/exit.c \
# 		builtin/cd_path.c builtin/pwd_path.c builtin/redir_file.c \
# 		builtin/redir_file_utils.c builtin/env_utils.c builtin/heredoc.c \
# 		builtin/heredoc_utils.c builtin/cd_path_utils.c

# UTILS = utilities/print_utils.c utilities/free_utils.c utilities/get_next_line.c \
# 		utilities/signals.c

# EXECS = executor/executor.c executor/executor_utils.c executor/pipex.c \
# 		executor/pipex_utils.c

# PARSER = parser/parser.c parser/lexer.c parser/lexer_utils.c parser/init_cmdgrp.c \
# 		 parser/redirection.c parser/command.c parser/expansion.c parser/expansion_size.c \
# 		 parser/expansion_replace.c parser/expansion_utils.c parser/arguments.c

OBJ = ${SRC:.c=.o} ${BLTIN:.c=.o} ${UTILS:.c=.o} ${PARSER:.c=.o} ${EXECS:.c=.o}

LIBFT_PATH = libft/
LIBFT = libft/libft.a

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT} $(MAIN)
	@${CC} ${CFLAGS} -o ${NAME} ${MAIN} ${OBJ} ${LIBFT} ${LDFLAGS}

${LIBFT}:
	@make re -C ${LIBFT_PATH}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@${RM} ${OBJ}
	@make clean -C ${LIBFT_PATH}

fclean: clean
	@${RM} ${NAME}
	@make fclean -C ${LIBFT_PATH}

re: fclean all

.PHONY = all clean fclean re