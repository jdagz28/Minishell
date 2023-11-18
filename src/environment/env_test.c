/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:14:58 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/18 20:34:22 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_parsing.h"
#include "expansion.h"
#include "builtins.h"
#include "environment.h"

extern char **environ;

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	int		env_len;
	char	*get_var;

	(void)argc;
	(void)argv;
	get_var = NULL;
	shell.env = strtab_cpy(env);
	if (ft_setenv("TEST", "TEST VALUE", &shell.env, 1) == EXIT_FAILURE)
		printf("ft_setenv failed");
	env_len = ft_arraylen(shell.env);
	for (int i = 0; i < env_len; i++)
		printf("%s\n", shell.env[i]);
	printf("%s\n\n", get_var);
	get_var = ft_get_env_var(shell.env, "TEST");
	printf("%s\n\n", get_var);
	strtab_free(shell.env);
	return (0);
}