/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:17:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/01 17:14:48 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_mode(char c, int mode)
{
	if (c == '"' && mode == NORMAL_MODE)
		mode = DOUBLE_MODE;
	else if (c == '\'' && mode == NORMAL_MODE)
		mode = SIMPLE_MODE;
	return (mode);
}

void	get_command(int *mode, char **save_ptr, char **token, char delim)
{
	*mode = check_mode(**save_ptr, *mode);
	(*save_ptr)++;
	while (**save_ptr && **save_ptr != delim)
	{
		if (**save_ptr == '\\' && *(*save_ptr + 1) == delim)
		{
			(*token) = append_char((*token), delim);
			(*save_ptr) += 2;
		}
		else
		{
			(*token) = append_char((*token), **save_ptr);
			(*save_ptr)++;
		}
	}
	if (**save_ptr == delim)
	{
		(*save_ptr)++;
		*mode = NORMAL_MODE;
	}
	else
		exit_error("Invalid format");
}

char	check_quote(char c)
{
	if (c == '"' || c == '\'')
		return (c);
	return ('\0');
}

char *check_separator(char *sep)
{
	if (ft_strncmp(sep, "<<", 2) == 0)
		return ("<<");
	if (ft_strncmp(sep, ">>", 2) == 0)
		return (">>");
	if (*sep == '|')
		return ("|");
	if (*sep == '<')
		return ("<");
	if (*sep == '>')
		return (">");
	return (NULL);
}

char	*ft_strtok(char *str, int *mode)
{
	static char	*save_ptr = NULL;
	char		*token;
	char		delim;
	char	*separator;

	token = "";
	if (str)
		save_ptr = str;
	separator = check_separator(save_ptr);
	if (!save_ptr || *save_ptr == '\0')
		return (NULL);
	if (separator)
	{
		save_ptr += ft_strlen(separator);
		return (separator);
	}
	while (*save_ptr)
	{
		delim = check_quote(*save_ptr);
		separator = check_separator(save_ptr);
		if (delim)
			get_command(mode, &save_ptr, &token, delim);
		else if (separator)
			return (token);
		else 
		{
			token = append_char(token, *save_ptr);
			save_ptr++;
		}
	}
	return (token);
}
