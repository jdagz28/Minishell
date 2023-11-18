# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 15:33:53 by tbarbe            #+#    #+#              #
#    Updated: 2023/03/03 16:29:53 by tbarbe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME	=	minishell

PARSER_SRCS			=	parsing.c\
						parse_pipeline.c\
						parse_simple_cmd.c\
						parser_utils.c\
						parser.c\
						clear_ast.c

LEXER_SRCS		= tokenizer.c\
						check_opred_tokens.c\
                        check_token.c\
						check_word_inquote.c\
                        check_word_tokens.c\
                        create_token.c\
                        tokenizer_utils.c\
						clear_tokens.c

SRCS	=	minishell.c \
			shell.c \
			strtab_utils.c \
			strmatrix_utils.c \
			env.c \
			user.c \
			pwd.c \
			utils.c \
			files.c \
			var.c \
			varlst.c \
			varcmd.c \
			exec.c \
			signal.c

INCLUDE	=	./include

PARSER_SRCS_	=	$(addprefix src/parser/, $(PARSER_SRCS))

LEXER_SRCS_	=		$(addprefix src/lexer/, $(LEXER_SRCS))

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
