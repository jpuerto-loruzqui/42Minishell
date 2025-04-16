/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:17:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/16 10:22:44 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_parser_expand_strtok(char *str, t_data *data, char delim)
{
	char	*tmp;

	tmp = str;
	if (data->last_token_type != T_HEREDOC)
	{
		if (delim != '\'' && ft_strncmp(str, "$?", 3) == 0)
		{
			free(str);
			tmp = ft_itoa(data->last_exit_code);
		}
		else if (delim != '\'' && ft_strchr(str, '$'))
		{
			tmp = ft_expand_cmd(str, data->env_arr);
		}
	}
	return (tmp);
}

static void	ft_get_command(int *mode, char **save_ptr, char **token,
	t_data *data)
{
	char	delim;
	char	*aux;
	int		i;

	aux = "";
	delim = ft_check_quote(**save_ptr);
	*mode = ft_check_mode(**save_ptr, *mode);
	(*save_ptr)++;
	i = 0;
	while ((*save_ptr)[i] && (*save_ptr)[i] != delim)
		i++;
	if (!(*save_ptr)[i])
	{
		data->error = true;
		ft_exit_error("Invalid format");
		return ;
	}
	aux = ft_substr(*save_ptr, 0, i);
	aux = ft_parser_expand_strtok(aux, data, delim);
	aux = ft_strjoin_free(*token, aux);
	*token = aux;
	*save_ptr += i + 1;
}

static void	ft_get_unquoted_token(char **save_ptr, char **token, t_data *data)
{
	char	*aux;
	int		i;

	i = 0;
	aux = "";
	while ((*save_ptr)[i]
		&& (*save_ptr)[i] != ' '
		&& !ft_check_separator(&(*save_ptr)[i])
		&& !ft_check_quote((*save_ptr)[i]))
		i++;
	aux = ft_substr(*save_ptr, 0, i);
	aux = ft_parser_expand_strtok(aux, data, 0);
	aux = ft_strjoin_free(*token, aux);
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
		return (s.save_ptr += ft_strlen(s.separator), ft_strdup(s.separator));
	while (*s.save_ptr)
	{
		if (ft_check_separator(s.save_ptr))
			return (s.token);
		else if (*s.save_ptr == ' ')
			return (s.save_ptr++, s.token);
		if (ft_check_quote(*s.save_ptr))
			ft_get_command(mode, &s.save_ptr, &s.token, data);
		else
		{
			if (ft_is_valid_char(*s.save_ptr) == 1)
				ft_get_unquoted_token(&s.save_ptr, &s.token, data);
		}
	}
	return (s.token);
}
