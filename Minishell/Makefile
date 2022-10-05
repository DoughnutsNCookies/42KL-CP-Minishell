# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maliew <maliew@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 10:52:13 by schuah            #+#    #+#              #
#    Updated: 2022/10/06 01:22:54 by maliew           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
LIBFT		=	libft.a
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		+=	-I/usr/local/opt/readline/include -g
# CFLAGS		+=	-fsanitize=address -g3
READLINE	=	-lreadline
READLINE	+=	-L/usr/local/opt/readline/lib
SRCS_FILES	=	ms_expanderhelper \
				ms_exporthelper \
				ms_parseinput \
				ms_expandstar \
				ms_executor \
				ms_expander \
				ms_helper \
				ms_signal \
				ms_export \
				ms_error \
				ms_unset \
				ms_main \
				ms_echo \
				ms_exit \
				ms_env \
				ms_pwd \
				ms_cd \
				ms_check_dangling \
				ms_cmd_list \
				ms_io_list \
				ms_lexer_utils \
				ms_lexer \
				ms_parser \
				ms_pipe_list \
				ms_pipe_list_utils \
				ms_token \
				ms_expander_tree \
				ms_executor_struct \
				ms_executor_tree \
				ms_executor_utils \
				ms_heredoc \
				ms_heredoc_tree_enqueue \
				ms_heredoc_tree_dequeue \
				tmp_print_cmd_list
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

.PHONY:			all libft clean fclean re