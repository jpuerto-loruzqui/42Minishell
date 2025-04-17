/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:17:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/17 14:35:38 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_parser_expand_strtok(char *str, t_data *data, char delim)
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

void manage_slash(char **str, char delim)
{
	char *tmp;
	char *start;

	if (!str || !*str)
		return ;

	start = *str;
	tmp = ft_strdup("");
	while (**str)
	{
		if (**str == '\\' && *(*str + 1) && *(*str + 1) == delim)
		{
			tmp = ft_append_char(tmp, delim);
			(*str) += 2;
		}
		if (is_valid_char(**str) == 1)
			tmp = append_char(tmp, **str);
		(*str)++;
	}
	free(start);
	*str = tmp;
}

int ft_check_format(char **save_ptr, char delim, int *i, t_data *data)
{
	while ((*save_ptr)[*i] && (*save_ptr)[*i] != delim)
	{
		if ((*save_ptr)[*i] == '\\' && (*save_ptr)[*i + 1] && (*save_ptr)[*i + 1] == delim)
			(*i) += 2;
		(*i)++;
	}
	if (!(*save_ptr)[*i])
	{
		data->error = true;
		exit_error("Invalid format");
		return (0);
	}
	return (1);
}

static void	ft_get_command(int *mode, char **save_ptr, char **token,
	t_data *data)
{
	char	delim;
	char	*aux;
	char 	*tmp;
	int		i;

	i = 0;
	aux = "";
	delim = ft_check_quote(**save_ptr);
	*mode = ft_check_mode(**save_ptr, *mode);
	(*save_ptr)++;
	if (!ft_check_format(save_ptr, delim, &i, data))
		return ;
	aux = ft_substr(*save_ptr, 0, i);
	ft_manage_slash(&aux, delim);
	tmp = ft_parser_expand_strtok(aux, data, delim);
	free(aux);
	aux = ft_strjoin(*token, tmp);
	free(tmp);
	free(*token);
	*token = aux;
	*save_ptr += i + 1;
}

static void	ft_get_unquoted_token(char **save_ptr, char **token, t_data *data)
{
	char	*aux;
	int		i;
	char	*tmp;

	i = 0;
	aux = "";
	while ((*save_ptr)[i]
		&& (*save_ptr)[i] != ' '
		&& !ft_check_separator(&(*save_ptr)[i])
		&& !ft_check_quote((*save_ptr)[i]))
		i++;
	aux = ft_substr(*save_ptr, 0, i);
	ft_manage_slash(&aux, 0);
	tmp = ft_parser_expand_strtok(aux, data, 0);
	free(aux);
	aux = ft_strjoin(*token, tmp);
	free(*token);
	free(tmp);
	*token = aux;
	*save_ptr += i;
}

char	*ft_check_separator(char *sep)
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

	ft_init_strtok_struct(&s, str);
	if (!s.save_ptr || *s.save_ptr == '\0')
		return (NULL);
	if (s.separator)
		return (s.save_ptr += ft_strlen(s.separator), s.separator);
	while (*s.save_ptr)
	{
		if (ft_check_separator(s.save_ptr))
			return (s.token);
		if (*s.save_ptr == ' ')
		{
			if (s.token && s.flag)
				return (s.save_ptr++, s.token);
			else
			{
				free(s.token);
				s.token = ft_strdup(" ");
				return(s.save_ptr++, s.token);	
			}
		}
		if (ft_check_quote(*s.save_ptr))
		{
			ft_get_command(mode, &s.save_ptr, &s.token, data);
			s.flag = 1;
		}
		else
		{
			ft_get_unquoted_token(&s.save_ptr, &s.token, data);
			s.flag = 1;
		}
	}
	return (s.token);
}
