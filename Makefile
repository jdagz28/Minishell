# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 15:33:53 by tbarbe            #+#    #+#              #
#    Updated: 2023/11/20 09:26:14 by jdagoy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME				=	minishell

OS					= $(shell uname -s)
USERNAME			= $(shell whoami)

ifeq ($(OS),Linux)
	FSANITIZE		= -fsanitize=leak -fsanitize=address
	MAC_INCLUDES	=
	MAC_LIBS		=
else
	FSANITIZE		= -fsanitize=address
	MAC_INCLUDES	= -I /Users/$(USERNAME)/.brew/opt/readline/include
	MAC_LIBS		= -L /Users/$(USERNAME)/.brew/opt/readline/lib
endif

ifdef fsanitizeoff
	FSANITIZE		=
endif

PARSER_SRCS			=	parsing.c\
						parse_pipeline.c\
						parse_simple_cmd.c\
						parser_utils.c\
						parser.c\
						clear_ast.c

LEXER_SRCS			= tokenizer.c\
						check_opred_tokens.c\
                        check_token.c\
						check_word_inquote.c\
                        check_word_tokens.c\
                        create_token.c\
                        tokenizer_utils.c\
						clear_tokens.c

SRCS				=	minishell.c \
						shell.c \
						strtab_utils.c \
						strmatrix_utils.c \
						env.c \
						user.c \
						pwd.c \
						utils.c \
						files.c \
						var.c \
						exec.c \
						signal.c \
						export.c

INCLUDE				=	./include
PARSER_SRCS_		=	$(addprefix src/parser/, $(PARSER_SRCS))
LEXER_SRCS_			=		$(addprefix src/lexer/, $(LEXER_SRCS))

SRCS_	=			$(addprefix src/, $(SRCS))


LIBFT	=	./libft/libft.a

CC		=	gcc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -lreadline

all:		${NAME}

${NAME}:	
			$(MAKE) -C ./libft
			echo "libft done"
			${CC} ${PARSER_SRCS_} ${LEXER_SRCS_} ${SRCS_} ${LIBFT} ${PRINTF} -I ${INCLUDE} -o ${NAME} ${CFLAGS}
			echo "minishell done"
			echo "use 'make only' to only compile the minishell"

clean:
			$(MAKE) clean -C ./libft

fclean: 	clean
			${RM} $(NAME) $(LIBFT)

re:			fclean all

only:		
			${CC} ${PARSER_SRCS_} ${LEXER_SRCS_} ${SRCS_} ${LIBFT} ${PRINTF} -I ${INCLUDE} -o ${NAME} ${CFLAGS}
			echo "minishell done"

.PHONY:		all clean fclean re
