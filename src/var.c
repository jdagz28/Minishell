#include "../include/minishell.h"

t_var *var_new(char *key, char *value)
{
    t_var *res;

    res = malloc(sizeof(t_var));
    if (!res)
        return (NULL);
    res->key = key;
    res->value = value;
    return (res);
}

void var_clear(void *addr)
{
    t_var *var;

    var = (t_var *)addr;
    if (!var)
        return;
    if (var->key)
        free(var->key);
    if (var->value)
        free(var->value);
    free(var);
}

int var_set(t_var *var, char *value)
{
    free(var->value);
    var->value = ft_strdup(value);
    if (!var->value)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
