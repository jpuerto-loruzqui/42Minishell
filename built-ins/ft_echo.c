#include "../minishell.h"

int ft_echo(char **arg) // no saca al > outfile
{
    bool newline;

    newline = true;
    arg++;
    if (ft_strncmp(*arg, "-n", 2) == 0)
    {
        newline = false;
        arg++;
    }
    while (*arg)
    {
        ft_putstr_fd(*arg, STDOUT_FILENO);
        ft_putchar_fd(' ', STDERR_FILENO);
        arg++;
    }
    if (newline == true)
        ft_putchar_fd('\n', STDERR_FILENO);
    return (1);
}