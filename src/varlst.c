#include "../include/minishell.h"

char *varlst_getvalue(t_list *lst, char *key)
{
    t_var *var;
    int len;

    while (lst)
    {
        var = (t_var *)lst->content;
        len = ft_strlen(var->key);
        if (var && ft_strncmp(var->key, key, len) == 0)
            return (var->value);
        lst = lst->next;
    }
    return (NULL);
}

int varlst_getid(t_list *lst, char *key)
{
    t_var *var;
    int len;
    int i;

    i = 0;
    while (lst)
    {
        var = (t_var *)lst->content;
        len = ft_strlen(var->key);
        if (var && ft_strncmp(var->key, key, len) == 0)
            return (i);
        lst = lst->next;
        i++;
    }
    return (-1);
}

int varlst_set(t_shell *shell, char *key, char *value)
{
    t_list *l;
    t_var *var;
    int len;

    l = shell->varlst;
    while (l)
    {
        var = (t_var *)l->content;
        len = ft_strlen(var->key);
        if (var && ft_strncmp(var->key, key, len) == 0)
            return (var_set(var, value));
        l = l->next;
    }
    var = var_new(key, value);
    if (!var)
        return (EXIT_FAILURE);
    ft_lstadd_back(&shell->varlst, ft_lstnew(var));
    return (EXIT_SUCCESS);
}

void varlst_unset(t_list **lst, char *key)
{
    int id;

    id = varlst_getid(*lst, key);
    if (id == -1)
        return;
    *lst = ft_lstpop(*lst, &var_clear, id);
}
