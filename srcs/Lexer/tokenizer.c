/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 23:09:27 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/01 22:44:29 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"

//! Tokenize first on major types: operator, redirect, word
//! Process further tokens to tag appropriate token types


/**
 * * Tokenizer
 * Tokenize input from readline, check each character for token type
 * Stores tokens in a linked list
 * @param input
 */

t_token	*tokenizer(char *input)
{
	char	*line;
	t_token	head;
	t_token	*current;

	line = ft_strdup(input);
	if (line == NULL)
		tk_error_manager("ft_strdup failed"); 
	head.next = NULL;
	current = &head;
	while (*line)
	{
		//TODO
		//1. Check for whitespaces and consume whitespaces;
		//2. Check if operator 
		//3. Check if redirect 
		//4. Check if word 
		//5. If not among the types - handle unknown token
		if (check_whitespace(&line, line))
			continue ;
		else if (is_operator(line))
			current->next = operator_token(&line, line);
		else if (is_redirect(line))
			current->next = redirect_token(&line, line);
		else if (is_word(line))
			current->next = word_token(&line, line);
		else
			printf("Unexpected Token\n");
		current = current->next;
	}
	// Create last token to have the TK_EOF;
	current->next = new_token(NULL, TK_EOF);
	return (head.next);

}

/**
 * * check_whitespace
 * check for whitespaces; skip if there are any
 * @param next_inline - line pointer
 * @param line - current line
 */
bool 	check_whitespace(char **next_inline, char *line)
{
	int	i;

	i = 0;
	if (ft_isspace(line[i]))
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		*next_inline = line[i];
		return (true);	
	}
	return (false);
}

/**
 *  *check_prefix
 *  helper function for is_operator and is_redirect
 * @param line
 * @param prefix - current operator being check against
*/
bool	startswith(char *line, char *prefix)
{
	if (ft_strncmp(line, prefix, ft_strlen(prefix)) == 0)
		return (true);
	return (false);
}


/**
 * * is_operator
 * check if line has a control operator and is either one of the ff
 *  "||", "&&", "&", ";", ";;", ";&", ";;&", "|", "|&", "(", ")", "\n"
 * @param line	- current line
 */
bool	is_operator(char *line)
{
	static char *const	operators[] = \
	{"||", "&&", ";", "|", "(", ")", "\n", "NULL"};
	int					i;

	i = 0;
	while (operators[i] != NULL)
	{
		if (check_prefix(line, operators[i]))
			return (true);
		i++;
	}
	return (false)
	
}

/**
 * * is_redirect
 * check if line is a redirect
 * "<" ">" "<<" ">>"
 * @param line	- current line
 */
bool	is_redirect(char *line)
{
	static char *const	redirect[] = {"<" ">" "<<" ">>", "NULL"};
	int					i;

	i = 0;
	while (redirect[i] != NULL)
	{
		if (check_prefix(line, redirect[i]))
			return (true);
		i++;
	}
	return (false);
}

/**
 * *is_metacharacter
 * check if current character in line is a metachracter
 * ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’. 
 * @param c - current char
*/
bool	is_metacharacter(char c)
{
	return (c && ft_strchr("|;()<>\n", c));
}

/**
 * * is_word
 * check if it just word without metacharacters and whitespaces
 * @param line -current line
*/
bool	is_word(char *line)
{
	int	i;

	i = 0;
	while(line[i] != '\0')
	{
		if (is_metacharacter(line[i]) || ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * * operator_token
 * extract and tag the operator token from the input line, if present
 * @param remaining - pointer to the remaining part of the input line 
 * after extracting the operator
 * @param line - current line
*/
t_token	*operator_token(char **remaining, char *line)
{
	static char *const	operators[] = \
	{"||", "&&", ";", "|", "(", ")", "\n", "NULL"};
	int					i;
	char				*operator;

	i = 0;
	while(operators[i] != "NULL")
	{
		if (startswith(line, operators[i]))
		{
			operator = ft_strdup(operators[i]);
			if (operator == NULL)
				tk_error_manager("ft_strdup failed"); 
			*remaining = line + ft_strlen(operator);
			return (create_token(operator, TK_OPERATOR));	
		}
		i++;
	}
	tk_error_manager("Unrecognized operator");
}

/**
 * * redirect_token
 * extract and tag redirect token from the input line, if present
 * @param remaining - pointer to the remaining part of the input line 
 * after extracting the redirect
 * @param line - current line
*/
t_token	*redirect_token(char **remaining, char *line)
{
	static char *const	redirects[] = {"<" ">" "<<" ">>", "NULL"};
	int					i;
	char				*redirect;

	i = 0;
	while(redirects[i] != "NULL")
	{
		if (startswith(line, redirects[i]))
		{
			redirect = ft_strdup(redirects[i]);
			if (redirect == NULL)
				tk_error_manager("ft_strdup failed"); 
			*remaining = line + ft_strlen(redirect);
			return (create_token(redirect, TK_REDIRECT));	
		}
		i++;
	}
	tk_error_manager("Unrecognized operator");
}

t_token	*create_token(char *word, t_tk_kind kind)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(token));
	if (token == NULL)
		tk_error_manager("Calloc failed");
	token->word = word;
	token->kind = kind;
	return (token);
}

void	tk_error_manager(char *error_msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}