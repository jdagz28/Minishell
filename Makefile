# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 15:33:53 by tbarbe            #+#    #+#              #
#    Updated: 2023/11/30 14:34:24 by tbarbe           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME				=	minishell

OS					= 	$(shell uname -s)
USERNAME			= 	$(shell whoami)

ifeq ($(OS),Linux)
	FSANITIZE		= 	-fsanitize=address -fsanitize=leak
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

EXECUTE_SRCS		=	exec_bin.c\
							exec_bin_utils.c\
							exec.c

EXIT_SRCS			=	exit_clean.c\
							exit_value.c

EXPAND_SRCS			=	expand_cmds.c\
							expand_replace_var_value.c\
							expand_utils.c\
							expand_var_realloc_argv.c\
							expand_vars_heredoc.c\
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

REDIRECT_SRCS			=	redirect.c\
							redirect_utils.c\
							file.c\
							here_doc.c

SHELL_SRCS			=	init_pwd.c\
							shell_prompt.c\
							shell.c\
							user.c\
							shell_level.c

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

OBJ_DIR				=	./objects/
OBJ_BUILTINS		=	$(addprefix $(OBJ_DIR), $(BUILTINS_SRCS:.c=.o))
OBJ_ENV				=	$(addprefix $(OBJ_DIR), $(ENV_SRCS:.c=.o))
OBJ_EXECUTE			=	$(addprefix $(OBJ_DIR), $(EXECUTE_SRCS:.c=.o))
OBJ_EXIT			=	$(addprefix $(OBJ_DIR), $(EXIT_SRCS:.c=.o))
OBJ_EXPAND			=	$(addprefix $(OBJ_DIR), $(EXPAND_SRCS:.c=.o))
OBJ_LEXER			=	$(addprefix $(OBJ_DIR), $(LEXER_SRCS:.c=.o))
OBJ_PARSER			=	$(addprefix $(OBJ_DIR), $(PARSER_SRCS:.c=.o))
OBJ_REDIRECT		=	$(addprefix $(OBJ_DIR), $(REDIRECT_SRCS:.c=.o))
OBJ_SHELL			=	$(addprefix $(OBJ_DIR), $(SHELL_SRCS:.c=.o))
OBJ_SIGNAL			=	$(addprefix $(OBJ_DIR), $(SIGNAL_SRCS:.c=.o))
OBJ_SRCS			=	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
OBJ_STRTAB			=	$(addprefix $(OBJ_DIR), $(STRTAB_SRCS:.c=.o))

HEADER_LIST			=	minishell.h\
						lexer_parsing.h\
						expansion.h\
						builtins.h\
						environment.h\
						execution.h\
						shell.h

HEADER_FILES		=	$(addprefix $(INCLUDE), $(HEADER_LIST))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: src/builtins/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: src/environment/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: src/execution/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: src/exit/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: src/expander/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: src/lexer/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: src/parser/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: src/redirection/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: src/shell/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: src/signals/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: src/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: src/strtab/%.c $(HEADER_FILES)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(NAME): $(OBJ_BUILTINS) $(OBJ_ENV) $(OBJ_EXECUTE) $(OBJ_EXIT) $(OBJ_EXPAND) \
	$(OBJ_LEXER) $(OBJ_PARSER) $(OBJ_REDIRECT) $(OBJ_SHELL) $(OBJ_SIGNAL) $(OBJ_SRCS) $(OBJ_STRTAB)
	@$(MAKE) -C ./libft
	@echo "libft done"
	@$(CC) $^ $(LIBFT) $(CFLAGS) $(LIBRARIES) $(INCLUDES) -o $@
	@echo "minishell done"
	@echo "use 'make only' to only compile the minishell"

clean:
	@$(MAKE) clean -C ./libft
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME) $(LIBFT)

re: fclean all

only:		
	@$(CC) $(OBJ_BUILTINS) $(OBJ_ENV) $(OBJ_EXECUTE) $(OBJ_EXIT) $(OBJ_EXPAND) \
	$(OBJ_LEXER) $(OBJ_PARSER) $(OBJ_REDIRECT) $(OBJ_SHELL) $(OBJ_SIGNAL) $(OBJ_SRCS) $(OBJ_STRTAB) \
	$(LIBFT) $(CFLAGS) $(INCLUDES) -o $(NAME)
	@echo "minishell done"

.PHONY: all clean fclean re
