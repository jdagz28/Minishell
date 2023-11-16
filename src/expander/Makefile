# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 15:33:53 by tbarbe            #+#    #+#              #
#    Updated: 2023/11/15 15:45:24 by jdagoy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= expander

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

CC					= cc
CFLAGS				= -Wall -Wextra -Werror -g $(FSANITIZE)
RM					= rm -rf

LIBFT_DIRECTORY		= ../../libft/
LIBFT				= $(LIBFT_DIRECTORY)libft.a

OBJECTS_DIRECTORY	= ./objects/
INCLUDE_DIRECTORY	= ../../include/
PARSER_DIRECTORY	= ../parser/
LEXER_DIRECTORY		= ../lexer/
EXPAND_DIRECTORY	= ./

LIBRARIES			= -lreadline -L$(LIBFT_DIRECTORY) -lft $(MAC_LIBS)
INCLUDES			= -I$(INCLUDE_DIRECTORY) $(MAC_INCLUDES)

HEADER_LIST			= minishell.h\
						lexer_parsing.h

HEADER_FILES		= $(addprefix $(INCLUDE_DIRECTORY), $(HEADER_LIST))

LEXER_SRCS_LIST		= tokenizer.c\
						check_opred_tokens.c\
                        check_token.c\
						check_word_inquote.c\
                        check_word_tokens.c\
                        create_token.c\
                        tokenizer_utils.c

PARSING_SRCS_LIST	= parse_pipeline.c\
						parse_simple_cmd.c\
						parser_utils.c\
						parser.c

EXPAND_SRCS_LIST	= expand_cmds.c\
						expand_replace_var_value.c\
						expand_utils.c\
						expand_var_realloc_argv.c\
						expand_vars_utils.c\
						expand_vars.c\
						remove_quotes.c\
						expand_test.c\
						free_array.c
                 
EXPAND_LIST			= $(patsubst %.c, %.o, $(EXPAND_SRCS_LIST))
EXPAND_OBJECTS		= $(addprefix $(OBJECTS_DIRECTORY), $(EXPAND_LIST))

PARSER_LIST			= $(patsubst %.c, %.o, $(PARSING_SRCS_LIST))
PARSER_OBJECTS				= $(addprefix $(OBJECTS_DIRECTORY), $(PARSER_LIST))

LEXER_LIST			= $(patsubst %.c, %.o, $(LEXER_SRCS_LIST))
LEXER_OBJECTS		= $(addprefix $(OBJECTS_DIRECTORY), $(LEXER_LIST))

all: $(NAME)
$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o: $(LEXER_DIRECTORY)/%.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o: $(PARSER_DIRECTORY)/%.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIRECTORY)%.o: $(EXPAND_DIRECTORY)/%.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@echo "$(NAME): Compiling $(LIBFT)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY) 

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(LEXER_OBJECTS) $(PARSER_OBJECTS) $(EXPAND_OBJECTS) $(HEADER_FILES)
	@echo "$(NAME)..."
	@$(CC) $(CFLAGS) $(LEXER_OBJECTS) $(PARSER_OBJECTS) $(EXPAND_OBJECTS) $(LIBRARIES) $(INCLUDES) -o $(NAME)

clean:
	$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	rm -rf $(OBJECTS_DIRECTORY)

fclean: clean
	$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
	rm -f $(NAME)

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --verbose --track-origins=yes ./$(NAME) 

.PHONY: all clean fclean re
