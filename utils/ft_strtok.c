/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:17:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/17 13:00:06 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*parser_expand_strtok(char *str, t_data *data, char delim)
{
	
	if (data->last_token_type != T_HEREDOC)
	{
		if (delim != '\'' && ft_strncmp(str, "$?", 3) == 0)
			return ft_itoa(data->last_exit_code);
		else if (delim != '\'' && ft_strchr(str, '$'))
			return expand_cmd(str, data->env_arr);
	}
	return ft_strdup(str);
}

static void	get_command(int *mode, char **save_ptr, char **token,
	t_data *data)
{
	char	delim;
	char	*aux;
	int		i;
	char 	*tmp;

	aux = "";

	delim = check_quote(**save_ptr);
	*mode = check_mode(**save_ptr, *mode);
	(*save_ptr)++;
	i = 0;
	while ((*save_ptr)[i] && (*save_ptr)[i] != delim)
		i++;
	if (!(*save_ptr)[i])
	{
		data->error = true;
		exit_error("Invalid format");
		return ;
	}
	aux = ft_substr(*save_ptr, 0, i);
	tmp = parser_expand_strtok(aux, data, delim);
	free(aux);
	aux = ft_strjoin(*token, tmp);
	free(tmp);
	free(*token);
	*token = aux;
	*save_ptr += i + 1;
}

static void	get_unquoted_token(char **save_ptr, char **token, t_data *data)
{
	char	*aux;
	int		i;
	char	*tmp;

	i = 0;
	aux = "";
	while ((*save_ptr)[i]
		&& (*save_ptr)[i] != ' '
		&& !check_separator(&(*save_ptr)[i])
		&& !check_quote((*save_ptr)[i]))
		i++;
	aux = ft_substr(*save_ptr, 0, i);
	tmp = parser_expand_strtok(aux, data, 0);
	free(aux);
	aux = ft_strjoin(*token, tmp);
	free(*token);
	free(tmp);
	*token = aux;
	*save_ptr += i;
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
	s.flag = 0;
	if (!s.save_ptr || *s.save_ptr == '\0')
		return (NULL);
	if (s.separator)
		return (s.save_ptr += ft_strlen(s.separator), s.separator);
	while (*s.save_ptr)
	{
		if (check_separator(s.save_ptr))
			return (s.token);
		if (*s.save_ptr == ' ')
		{
			if (s.token && s.flag)
				return (s.save_ptr++, s.token);
			else
			{
				s.save_ptr++;
				free(s.token);
				s.token = ft_strdup(" ");
				return(s.token);	
			}
		}
		if (check_quote(*s.save_ptr))
		{
			get_command(mode, &s.save_ptr, &s.token, data);
			s.flag = 1;
		}
		else
		{
			if (is_valid_char(*s.save_ptr) == 1)
				get_unquoted_token(&s.save_ptr, &s.token, data);
		}
	}
	return (s.token);
}
