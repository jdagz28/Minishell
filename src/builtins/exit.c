/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdagoy <jdagoy@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:48:32 by jdagoy            #+#    #+#             */
/*   Updated: 2023/11/22 15:02:10 by jdagoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

int	exit(char **argv)
{
	int		exit_value;
	int		arg_count;

	exit_value = *get_exit_value();
	arg_count = strtab_len(argv);
	if (arg_count > 1)
	{
		if (ft_isnum(argv[1]) == false)
		{
			print_error(argv[1], "numeric argument required\n")
			status = 2;
		}
}