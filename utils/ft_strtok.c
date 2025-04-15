/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:17:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/15 11:28:45 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_command(int *mode, char **save_ptr, char **token, t_data *data)
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
			if (is_valid_char(**save_ptr) == 1)
				(*token) = append_char((*token), **save_ptr);
			(*save_ptr)++;
		}
	}
	if (**save_ptr != delim)
	{
		data->error = true;
		exit_error("Invalid format");
	}
	else
	{
		(*mode) = NORMAL_MODE;
		(*save_ptr)++;
	}
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
	static t_strtok	s;

	init_strtok_struct(&s, str);
	if (!s.save_ptr || *s.save_ptr == '\0')
		return (NULL);
	if (s.separator)
		return (s.save_ptr += ft_strlen(s.separator), ft_strdup(s.separator));
	while (*s.save_ptr)
	{
		if (check_separator(s.save_ptr))
			return (s.token);
		else if (*s.save_ptr == ' ')
			return (s.save_ptr++, s.token);
		if (check_quote(*s.save_ptr))
			get_command(mode, &s.save_ptr, &s.token, data);
		else
		{
			if (is_valid_char(*s.save_ptr) == 1)
				s.token = append_char(s.token, *s.save_ptr);
			s.save_ptr++;
		}
	}
	return (s.token);
}
