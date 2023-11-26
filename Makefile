# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 15:33:53 by tbarbe            #+#    #+#              #
#    Updated: 2023/11/25 18:47:34 by jdagoy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME				=	minishell

OS					= 	$(shell uname -s)
USERNAME			= 	$(shell whoami)

ifeq ($(OS),Linux)
	FSANITIZE		= 	#-fsanitize=address -fsanitize=leak 
	MAC_INCLUDES	=
	MAC_LIBS		=
else
	FSANITIZE		= 	-fsanitize=address
	MAC_INCLUDES	= 	-I /Users/$(USERNAME)/.brew/opt/readline/include
	MAC_LIBS		= 	-L /Users/$(USERNAME)/.brew/opt/readline/lib
endif

ifdef fsanitizeoff
	FSANITIZE		=
endif

ifdef debug
	FSANITIZE		= 	-g
endif

CC					=	cc
RM					=	rm -f
CFLAGS				=	-Wall -Wextra -Werror $(FSANITIZE)

LIBFT				=	./libft/libft.a

LIBRARIES			= 	-lreadline $(MAC_LIBS)	

BUILTINS_SRCS		=	builtins.c\
							cd.c\
							cd_errors.c\
							echo.c\
							exit.c\
							export.c\
							pwd.c\
							unset.c

ENV_SRCS			=	env_getvar.c\
							env_set.c\
							vartab_set_unset.c\
							vartab_pos.c\
							var_key.c\
							var_set.c

EXECUTE_SRCS		=	exec_binpath.c\
							exec_utils.c\
							exec.c

EXIT_SRCS			=	exit_clean.c\
							exit_value.c

EXPAND_SRCS			=	expand_cmds.c\
							expand_replace_var_value.c\
							expand_utils.c\
							expand_var_realloc_argv.c\
							expand_vars_utils.c\
							expand_vars.c\
							free_array.c\
							remove_quotes_utils.c\
							remove_quotes.c\
							checktab_for_var.c

LEXER_SRCS			=	check_opred_tokens.c\
							check_token.c\
							check_word_inquote.c\
							check_word_tokens.c\
							clear_tokens.c\
							create_token.c\
							tokenizer_utils.c\
							tokenizer.c

PARSER_SRCS			=	clear_ast.c\
							parse_pipeline.c\
							parse_simple_cmd.c\
							parser_utils.c\
							parser.c\
							parsing.c

REDIRECT_SRCS			=	files.c

SHELL_SRCS			=	init_pwd.c\
							shell_prompt.c\
							shell.c\
							user.c

SIGNAL_SRCS			=	signal.c

SRCS				=	minishell.c\
							utils.c

STRTAB_SRCS			=		strtab_add.c\
							strtab_replace.c\
							strtab_remove.c\
							strtab_free.c\
							strtab_utils.c\


INCLUDE				=	./include/
INCLUDES			= 	-I $(INCLUDE) $(MAC_INCLUDES)
BUILTINS_SRCS_		=	$(addprefix src/builtins/, $(BUILTINS_SRCS))
ENV_SRCS_			= 	$(addprefix src/environment/, $(ENV_SRCS))
EXECUTE_SRCS_		=	$(addprefix src/execution/, $(EXECUTE_SRCS))
EXIT_SRCS_			= 	$(addprefix src/exit/, $(EXIT_SRCS))
EXPAND_SRCS_		= 	$(addprefix src/expander/, $(EXPAND_SRCS))
LEXER_SRCS_			=	$(addprefix src/lexer/, $(LEXER_SRCS))
PARSER_SRCS_		=	$(addprefix src/parser/, $(PARSER_SRCS))
REDIRECT_SRCS_		=	$(addprefix src/redirection/, $(REDIRECT_SRCS))
SHELL_SRCS_			= 	$(addprefix src/shell/, $(SHELL_SRCS))
SIGNAL_SRCS_		=	$(addprefix src/signals/, $(SIGNAL_SRCS))
SRCS_				=	$(addprefix src/, $(SRCS))
STRTAB_SRCS_		=	$(addprefix src/strtab/, $(STRTAB_SRCS))


HEADER_LIST			=	minishell.h\
						lexer_parsing.h\
						expansion.h\
						builtins.h\
						environment.h\
						execution.h\
						shell.h

HEADER_FILES		=	$(addprefix $(INCLUDE), $(HEADER_LIST))

all:		${NAME}

${NAME}:	
			$(MAKE) -C ./libft
			echo "libft done"
			${CC} ${BUILTINS_SRCS_} ${ENV_SRCS_} ${EXECUTE_SRCS_} \
			${EXIT_SRCS_} ${EXPAND_SRCS_} ${LEXER_SRCS_} ${PARSER_SRCS_} ${STRTAB_SRCS_} \
			${REDIRECT_SRCS_} ${SHELL_SRCS_} ${SIGNAL_SRCS_} ${SRCS_} ${LIBFT} ${HEADER_FILES} \
			${INCLUDES} -o ${NAME} ${CFLAGS} ${LIBRARIES}
			echo "minishell done"
			echo "use 'make only' to only compile the minishell"

clean:
			$(MAKE) clean -C ./libft

fclean: 	clean
			${RM} $(NAME) $(LIBFT)

re:			fclean all

only:		
			${CC} ${BUILTINS_SRCS_} ${ENV_SRCS_} ${EXECUTE_SRCS_} \
			${EXIT_SRCS_} ${EXPAND_SRCS_} ${LEXER_SRCS_} ${PARSER_SRCS_} ${STRTAB_SRCS_} \
			${REDIRECT_SRCS_} ${SHELL_SRCS_} ${SIGNAL_SRCS_} ${SRCS_} ${LIBFT} ${HEADER_FILES} \
			${INCLUDES} -o ${NAME} ${CFLAGS} ${LIBRARIES}
			echo "minishell done"

.PHONY:		all clean fclean re
