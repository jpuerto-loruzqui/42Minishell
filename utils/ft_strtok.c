/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:17:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/09 19:17:32 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*save_ptr = NULL;
	char		*start;

	if (str)
		save_ptr = str;
	if (!save_ptr || *save_ptr == '\0')
		return (NULL);
	while (*save_ptr && ft_strchr(delim, *save_ptr))
		save_ptr++;
	if (*save_ptr == '\0')
		return (NULL);
	start = save_ptr;
	while (*save_ptr && !ft_strchr(delim, *save_ptr))
		save_ptr++;
	if (*save_ptr)
	{
		*save_ptr = '\0';
		save_ptr++;
	}
	return (start);
}
