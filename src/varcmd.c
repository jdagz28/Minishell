/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarbe <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:43:09 by tbarbe            #+#    #+#             */
/*   Updated: 2023/10/09 13:26:05 by tbarbe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void var_split(char *str, char **key, char **value)
{
    int start;
    int sep;

    sep = ft_strrchr(str, '=') - str;
    *key = ft_strndup(str, sep);
    start = sep + 1;
    *value = ft_strdup(&str[start]);
}

int var_unset(t_shell *shell, t_node *node) // unprotected
{
    t_simple_cmd cmd;
    char **argv;

    cmd = node->content.simple_cmd;
    argv = cmd.argv;
    if (cmd.has_quotes)
        return (0);
    if (ft_strlen(argv[0]) == 5 && ft_strncmp("unset", argv[0], 5) == 0 && argv[1])
    {
        varlst_unset(&shell->varlst, argv[1]);
        return (2);
    }
    return (0);
}

int var_extract(t_shell *shell, t_node *node) // unprotected
{
    t_simple_cmd cmd;
    char **argv;
    char *key;
    char *value;
    int i;

    cmd = node->content.simple_cmd;
    argv = cmd.argv;
    if (cmd.has_quotes)
        return (0);
    i = 0;
    while (argv[i] && ft_strchr(argv[i], '='))
    {
        var_split(argv[i], &key, &value);
        varlst_set(shell, key, value);
        i++;
    }
    return (i);
}

int var_inject(t_shell *shell, t_node *node)
{
    t_simple_cmd cmd;
    char **argv;
    char *str;
    char *value;
    int i;

    cmd = node->content.simple_cmd;
    argv = cmd.argv;
    if (cmd.has_quotes)
        return (0);
    i = 0;
    str = argv[i];
    while (str)
    {
        if (str[0] == '$')
        {
            value = varlst_getvalue(shell->varlst, &str[1]);
            if (value)
            {
                free(str);
                str = ft_strdup(value); // unprotected
            }
            else
                memset(str, 0, ft_strlen(str));
        }
        i++;
        str = argv[i];
    }
    return (i);
}
