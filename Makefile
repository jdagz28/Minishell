# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 15:33:53 by tbarbe            #+#    #+#              #
#    Updated: 2023/10/30 21:56:27 by jdagoy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME	=	minishell

SRCS	=	minishell.c \
			shell.c \
			strtab_utils.c \
			strmatrix_utils.c \
			pipes.c \
			commands.c \
			env.c \
			user.c \
			pwd.c \
			utils.c

INCLUDE	=	./include

SRCS_	=	$(addprefix src/, $(SRCS))

LIBFT	=	./libft/libft.a

CC		=	cc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -lreadline

all:		${NAME}

${NAME}:	
			$(MAKE) -C ./libft
			echo "libft done"
			${CC} ${SRCS_} ${LIBFT} ${PRINTF} -I ${INCLUDE} -o ${NAME} ${CFLAGS}
			echo "minishell done"
			echo "use 'make only' to only compile the minishell"

clean:
			$(MAKE) clean -C ./libft

fclean: 	clean
			${RM} $(NAME) $(LIBFT)

re:			fclean all

only:		
			${CC} ${SRCS_} ${LIBFT} ${PRINTF} -o ${NAME} ${CFLAGS}
			echo "minishell done"

.PHONY:		all clean fclean re
