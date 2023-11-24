/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:48:32 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/23 09:03:25 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

int	builtin_exit(char **argv, t_shell *shell)
{
	int		exit_value;
	int		arg_count;

	exit_value = *get_exit_value();
	arg_count = strtab_len(argv);
	if (*is_piped() == false)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (arg_count > 1)
	{
		if (ft_isnum(argv[1]) == false)
		{
			print_error(argv[1], "numeric argument required\n");
			exit_value = 2;
		}
		else if (arg_count > 2)
		{
			print_error(argv[1], "too many arguments\n");
			return (EXIT_FAILURE);
		}
		else
			exit_value = ft_atoi(argv[1]);
	}
	if (*is_piped() == false)
		clean_exit(shell, exit_value);
	return (exit_value);
}
