# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 10:52:13 by schuah            #+#    #+#              #
#    Updated: 2022/10/11 13:08:37 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
LIBFT		=	libft.a
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		+=	-I/usr/local/opt/readline/include
CFLAGS		+=	-fsanitize=address -g3
READLINE	=	-lreadline
READLINE	+=	-L/usr/local/opt/readline/lib
SRCS_FILES	=	ms_heredoc_tree_enqueue \
				ms_heredoc_tree_dequeue \
				ms_executor_struct \
				ms_check_dangling \
				ms_executor_utils \
				ms_expand_dollar \
				ms_expand_second \
				ms_expander_tree \
				ms_executor_tree \
				ms_expand_first \
				ms_export_utils \
				ms_expand_files \
				ms_parse_input \
				ms_expand_star \
				ms_lexer_utils \
				ms_executor_io \
				ms_get_abspath \
				ms_list_utils \
				ms_pipe_list \
				ms_executor \
				ms_expander \
				ms_cmd_list \
				ms_io_list \
				ms_heredoc \
				ms_helper \
				ms_signal \
				ms_export \
				ms_parser \
				ms_error \
				ms_unset \
				ms_lexer \
				ms_token \
				ms_main \
				ms_echo \
				ms_exit \
				ms_env \
				ms_pwd \
				ms_cd
SRCS		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRCS_FILES)))
OBJS		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS_FILES)))
SRCS_DIR	=	srcs/
LIBFT_DIR	=	libft
OBJS_DIR	=	objs/

all:			
				mkdir -p $(OBJS_DIR)
				make libft
				make $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $^ $(READLINE) -Llibft -lft -o $@
				
libft:
				make -C $(LIBFT_DIR)

clean:
				rm -rf $(OBJS_DIR)
				make clean -C $(LIBFT_DIR)

fclean:			clean
				make fclean -C $(LIBFT_DIR)
				rm -rf $(NAME)

re:				fclean all

valgrind:
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./minishell

.PHONY:			all libft clean fclean re