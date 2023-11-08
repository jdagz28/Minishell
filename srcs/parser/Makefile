# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 15:33:53 by tbarbe            #+#    #+#              #
#    Updated: 2023/11/08 10:54:09 by jdagoy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= parser

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
SOURCES_DIRECTORY	= ./
LEXER_DIRECTORY		= ../lexer/

LIBRARIES			= -lreadline -L$(LIBFT_DIRECTORY) -lft $(MAC_LIBS)
INCLUDES			= -I$(INCLUDE_DIRECTORY) $(MAC_INCLUDES)

HEADER_LIST			= minishell.h\
						lexer_parsing.h

HEADER_FILES		= $(addprefix $(INCLUDE_DIRECTORY), $(HEADER_LIST))

LEXER_LIST			= check_opred_tokens.c\
                        check_token.c\
						check_word_inquote.c\
                        check_word_tokens.c\
                        create_token.c\
                        tokenizer_utils.c\
                        tokenizer.c

LEXER_LIST			= $(patsubst %.c, %.o, $(LEXER_LIST))
LEXER_OBJECTS		= $(addprefix $(OBJECTS_DIRECTORY), $(LEXER_LIST))

SRCS_LIST			= parsing_test.c
                        

OBJECTS_LIST		= $(patsubst %.c, %.o, $(SRCS_LIST))
OBJECTS				= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

all: $(NAME)
$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)

$(OBJECTS_DIRECTORY)%.o: $(SOURCES_DIRECTORY)/%.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	@echo "$(NAME): Compiling $(LIBFT)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY) 

$(NAME): $(LIBFT) $(OBJECTS_DIRECTORY) $(OBJECTS) $(HEADER_FILES)
	@echo "$(NAME)..."
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBRARIES) $(INCLUDES) -o $(NAME)

clean:
	$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	rm -rf $(OBJECTS_DIRECTORY)
	rm -rf *.dSYM

fclean: clean
	$(MAKE) -sC $(LIBFT_DIRECTORY) fclean
	rm -f $(NAME)

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --leak-check=full --track-origins=yes ./$(NAME) 

.PHONY: all clean fclean re
