/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:17:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/11 09:54:56 by loruzqui         ###   ########.fr       */
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

char	check_quote(char c)
{
	if (c == '"' || c == '\'')
		return (c);
	return ('\0');
}

void	get_command(int *mode, char **save_ptr, char **token, t_data *data)
{
	char	delim;

	delim = check_quote(**save_ptr);
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
	if (**save_ptr != delim)
	{
		data->error = true;
		exit_error("Invalid format");
	}
	(*save_ptr)++;
}

char	*check_separator(char *sep)
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

char	*ft_strtok(char *str, int *mode, t_data *data)
{
	static char	*save_ptr = NULL;
	char		*token;
	char		*separator;

	token = "";
	if (str)
		save_ptr = str;
	separator = check_separator(save_ptr);
	if (!save_ptr || *save_ptr == '\0')
		return (NULL);
	if (separator)
		return (save_ptr += ft_strlen(separator), ft_strdup(separator));
	while (*save_ptr)
	{
		if (check_separator(save_ptr))
			return (token);
		else if (*save_ptr == ' ')
			return (save_ptr++, token);
		if (check_quote(*save_ptr))
			get_command(mode, &save_ptr, &token, data);
		else
			token = append_char(token, *save_ptr++);
	}
	return (token);
}
