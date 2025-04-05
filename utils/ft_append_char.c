/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:58:07 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/04/01 14:13:42 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *append_char(char *str, char c)
{
    size_t len = ft_strlen(str);
    char *new_str = malloc(len + 2);
    if (!new_str)
        return NULL;
    ft_strlcpy(new_str, str, len + 1);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    if (str && str[0])
        free(str);
    return new_str;
}