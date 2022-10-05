# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 10:52:13 by schuah            #+#    #+#              #
#    Updated: 2022/10/05 18:57:59 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
LIBFT		=	libft.a
CC			=	gcc
RM			=	rm -f
CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		+=	-I/usr/local/opt/readline/include
# CFLAGS		+=	-fsanitize=address -g3
READLINE	=	-lreadline
READLINE	+=	-L/usr/local/opt/readline/lib
SRCS_FILES	=	ms_expand_dollar \
				ms_expand_utils \
				ms_export_utils \
				ms_expand_quote \
				ms_expand_files \
				ms_parse_input \
				ms_expand_star \
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
				temp_debugger
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