/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 13:26:05 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "environment.h"

static int redirect_input(char* type, char* dest)
{
	int err;

	err = EXIT_SUCCESS;
	if (ft_strlen(type) == 2 && type[1] == '<')
		err = read_here_doc(dest);
	else
		err = open_file_dup2(dest, 'r');
	if (err)
		print_error(dest, strerror(errno));
	return(err);
}

static int redirect_output(char* type, char* dest)
{
	int err;
	char c;

	c = 'w';
	if (ft_strlen(type) == 2 && type[1] == '>')
		c = 'a';
	err = open_file_dup2(dest, c);
	if (err)
		print_error(dest, strerror(errno));
	return(err);
}

int redirect_one(char* type, char* dest)
{
	char c;

	//ft_printf("%s %s\n", type, dest);
	c = type[0];
	if (c == '<')
		redirect_input(type, dest);
	else if (c == '>')
		redirect_output(type, dest);
	else
		return(0);
	return(1);
}

int redirect(char*** tab)
{
	char** cmd;
	int len;
	int i;

	cmd = *tab;
	len = strtab_len(cmd);
	i = 0;
	while (i < len)
	{
		if (redirect_one(cmd[i], cmd[i + 1]))
			return(strtab_remove_mult(tab, i, 2));
		i++;
	}
	return (EXIT_SUCCESS);
}
