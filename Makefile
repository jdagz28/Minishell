# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 15:33:53 by tbarbe            #+#    #+#              #
#    Updated: 2023/10/31 22:59:39 by jdagoy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME				= minishell

OS					= $(shell uname -s)
USERNAME			= $(shell whoami)

ifeq ($(OS),Linux)
	FSANITIZE		= -fsanitize=leak -fsanitize=address
	MAC_INCLUDES	=
	MAC_LIBS		=
else
	FSANITIZE		= -fsanitize=address
	MAC_INCLUDES	= -I /Users/$(USERNAME)/Applications/homebrew/opt/readline/include
	MAC_LIBS		= -L /Users/$(USERNAME)/Applications/homebrew/opt/readline/lib
endif

CC					= cc
CFLAGS				= -Wall -Wextra -Werror $(FSANITIZE)
RM					= rm -rf

SRCS_DIRECTORY		= ./srcs/
OBJS_DIRECTORY		= ./objects/
INCLUDES			= ./include/

LIBRARIES			= -lreadline 

LIBFT	=	./libft/libft.a
# SRCS		=	minishell.c \
# 				shell.c \
# 				strtab_utils.c \
# 				strmatrix_utils.c \
# 				pipes.c \
# 				commands.c \
# 				env.c \
# 				user.c \
# 				pwd.c \
# 				utils.c



SRCS_	=	$(addprefix srcs/, $(SRCS))

OBJS_LIST	=
OBJECTS     =



all:		${NAME}
$(OBJS_DIRECTORY)
	mkdir -p $(OBJECTS_DIRECTORY)


${NAME}:	
			$(MAKE) -C ./libft
			echo "libft done"
			${CC} ${SRCS_} ${LIBFT} ${PRINTF} -I ${INCLUDES} -o ${NAME} ${CFLAGS}
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
