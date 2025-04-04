#include "../minishell.h"

int get_env_size(char **args, char **envp)
{
    int size = 0;
    int i = 0;
    int j;

    while (envp[i]) {
        j = 0;
        while (args[j])
        {
            if (strncmp(envp[i], args[j], strlen(args[j])) == 0 && envp[i][strlen(args[j])] == '=')
                break;
            j++;
        }
        if (!args[j])
            size++;
        i++;
    }
    return (size);
}

char **ft_unset(char **args, char ***envp)
{
    char **new_env;
    int size;
    int i;
    int j;
    int k;

    i = 0;
    k = 0;
    size = get_env_size(args, *envp);
    new_env = malloc(sizeof(char *) * (size + 1));
    if (!new_env)
        return NULL;
    while ((*envp)[i]) {
        j =-1;
        while (args[++j])
            if (strncmp((*envp)[i], args[j], strlen(args[j])) == 0 && (*envp)[i][strlen(args[j])] == '=')
                break;
        if (!args[j])
            new_env[k++] = (*envp)[i];
        i++;
    }
    // if (*envp != NULL)
    //     ft_free_split(*envp);
    new_env[k] = NULL;
    return new_env;
}
