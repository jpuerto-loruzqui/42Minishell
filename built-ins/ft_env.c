#include "../minishell.h"

int ft_env(char **args, char **envp)
{
    (void)args;
    while (*envp)
    {
        ft_putstr_fd(*envp, STDOUT_FILENO);
        ft_putchar_fd('\n', STDOUT_FILENO);
        envp++;
    }
    return (1);
}