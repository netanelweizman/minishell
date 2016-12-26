# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nweizman <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/07 12:28:33 by nweizman          #+#    #+#              #
#    Updated: 2016/12/07 12:28:35 by nweizman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	"minishell"

C_FILES		=	src/main.c					\
				gnl/get_next_line.c			\
				src/mng_notes.c				\
				src/notes.c					\
				src/mng_thread.c			\
				src/cmd_cd.c				\
				src/cmd_echo.c				\
				src/cmd_env.c				\
				src/cmd_program.c			\
				src/env_funcs.c				\
				src/global.c				\
				src/cmd_exit.c				\
				src/flags.c					\
				src/cmd_polo.c

O_FILES		=	src/main.o					\
				gnl/get_next_line.o			\
				src/mng_notes.o				\
				src/notes.o					\
				src/mng_thread.o			\
				src/cmd_cd.o				\
				src/cmd_echo.o				\
				src/cmd_env.o				\
				src/cmd_program.o			\
				src/env_funcs.o				\
				src/global.o				\
				src/cmd_exit.o				\
				src/flags.o					\
				src/cmd_polo.o

CC			=	gcc -Wall -Werror -Wextra

LIBFT		=	-L libft -lft -L libft/ft_printf -lftprintf

all: $(NAME)

$(NAME): $(O_FILES)
	@make -C libft
	@$(CC) -o $(NAME) $(C_FILES) $(LIBFT)

clean:
	@make clean -C libft
	@/bin/rm -f $(O_FILES)

fclean: clean
	@make fclean -C libft
	@/bin/rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
