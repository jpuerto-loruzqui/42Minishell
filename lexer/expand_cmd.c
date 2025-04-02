#include "../minishell.h"

char *expand_cmd(t_lexer token)
{
    char *aux;
    char *str;
    char *cmd;

    cmd = "";
    str = token.data;
    aux = "";
    while (*str)
    {
        if (*str == '$')
        {
            str++;
            if (*str && *str == '{')
                str++;
            while (*str && *str != '"' && *str != '\'' && *str != '}' && str != ' ')
            {
                cmd = append_char(cmd, *str);
                // aqui buscariamos lo que trae cmd
            }
            if (cmd && cmd[0])
                aux = ft_strjoin(aux, cmd);
            if (*str && *str == '}')
                str++;
        }
        aux = append_char(aux, *str);
        str++;
    }
}
