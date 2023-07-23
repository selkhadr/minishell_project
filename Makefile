# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/02 19:04:47 by mel-moun          #+#    #+#              #
#    Updated: 2023/07/23 19:12:04 by selkhadr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
CC=cc
fd_printf=fd_printf/libftprintf.a
libft=libft/libft.a
LDFLAGS= -L/Users/selkhadr/.brew/opt/readline/lib
CPPFLAGS= -I/Users/selkhadr/.brew/opt/readline/include
CFLAGS=-Wall -Wextra -Werror #-g -fsanitize=address
ARGS =-Iinclude -lreadline -L /Users/selkhadr/.brew/opt/readline/lib -I /Users/selkhadr/.brew/opt/readline/include
SRC= builtins_execution.c\
	builtins_execution_sequel.c\
	change_line.c\
	change_line_utils.c\
	environment.c\
	errors.c\
	execution.c\
	execution_utils.c\
	expand.c\
	expand_utils.c\
	expand_utils2.c\
	expand_utils3.c\
	first_linked_list.c\
	mer_itoa.c\
	mer_split.c\
	heredoc_execution.c\
	in_redctn_execution.c\
	manage_linked.c\
	manage_linked1.c\
	manage_linked3.c\
	minishell.c\
	out_redctn_execution.c\
	path_execution.c\
	print_nodes.c\
	prompt.c\
	redirection_execution.c\
	string.c\
	string1.c\
	string3.c\
	string4.c\
	tokenizer_part1.c\
	tokenizer_part2.c\
	tokenizer_utils.c\
	tokenizer_utils2.c\
	tokenizer_utils3.c\
	utils1_first_linked.c\
	utils2_first_linked.c\
	utils_first_linked.c\

OBJ=$(SRC:.c=.o)

all: $(NAME)

$(fd_printf):
	make -C fd_printf

$(libft):
	make -C libft

$(NAME): $(SRC) $(fd_printf) $(libft)
	$(CC) $(CFLAGS) $(SRC) $(fd_printf) $(libft) $(ARGS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C fd_printf clean
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C fd_printf fclean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean  all

.PHONY: all clean fclean re
