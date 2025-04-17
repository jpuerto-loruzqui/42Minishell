/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- & loruzqui < >                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:17:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/17 17:29:59 by jpuerto- &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_mode(char c, int mode)
{
	if (c == '"' && mode == NORMAL_MODE)
		mode = DOUBLE_MODE;
	else if (c == '\'' && mode == NORMAL_MODE)
		mode = SIMPLE_MODE;
	return (mode);
}

char	ft_check_quote(char c)
{
	if (c == '"' || c == '\'')
		return (c);
	return ('\0');
}

void	ft_init_strtok_struct(t_strtok *s, char *str)
{
	if (str)
		s->save_ptr = str;
	s->separator = ft_check_separator(s->save_ptr);
	if (s->token)
	{
		free(s->token);
		s->token = NULL;
	}
	s->token = ft_strdup("");
	s->flag = 0;
}

void	ft_manage_slash(char **str, char delim)
{
	char	*tmp;
	char	*start;

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
		if (ft_is_valid_char(**str) == 1)
			tmp = ft_append_char(tmp, **str);
		(*str)++;
	}
	free(start);
	*str = tmp;
}

int	ft_check_format(char **save_ptr, char delim, int *i, t_data *data)
{
	while ((*save_ptr)[*i] && (*save_ptr)[*i] != delim)
	{
		if ((*save_ptr)[*i] == '\\' && (*save_ptr)[*i + 1]
			&& (*save_ptr)[*i + 1] == delim)
			(*i) += 2;
		(*i)++;
	}
	if (!(*save_ptr)[*i])
	{
		data->error = true;
		ft_exit_error("Invalid format");
		return (0);
	}
	return (1);
}
