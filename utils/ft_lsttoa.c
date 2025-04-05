#include "../minishell.h"

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char **ft_lstoa(t_env *env)
{
    char **result;
    int     size;
    int     i;

    i = 0;
    size = ft_lstsize(env);
    result = malloc(sizeof(char *) * (size + 1));
    if (!result)
        return (NULL);
    while (env != NULL)
    {
        result[i] = env->content;
        i++;
        env = env->next;
    }
    return (result);
}