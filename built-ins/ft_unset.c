/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:00:40 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/08 13:02:24 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env *ft_unset(char **args, t_env *envp)
{
    t_env *current = envp;
    t_env *temp;
    t_env *prev = NULL;
    int i;

    while (current)
    {
        i = 0;
        while (args[i])
        {
            if (strncmp(current->content, args[i], strlen(args[i])) == 0
                && current->content[strlen(args[i])] == '=')
            {
                if (prev)
                    prev->next = current->next;
                else
                    current = current->next;
                temp = current;
                current = current->next;
                free(temp->content);
                free(temp);
                break;
            }
            i++;
        }
        if (!args[i])
        {
            prev = current;
            current = current->next;
        }
    }
    return envp; 
}

