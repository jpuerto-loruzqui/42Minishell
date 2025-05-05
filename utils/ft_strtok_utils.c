/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:17:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/05 10:05:16 by jpuerto          ###   ########.fr       */
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

char	ft_check_quote(char *c)
{
	if ((*c == '\\' && *c + 1) && (*c + 1 == '\"' || *c + 1 == '\"'))
		return ('\0');
	if (*c == '"' || *c == '\'')
		return (*c);
	return ('\0');
}

bool	ft_is_not_escaped(char *ptr, int i)
{
	int	count;

	count = 0;
	if (i == 0)
		return (true);
	i--;
	while (i >= 0 && ptr[i] == '\\')
	{
		count++;
		i--;
	}
	return (count % 2 == 0);
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
			continue ;
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
	while ((*save_ptr)[*i])
	{
		if ((*save_ptr)[*i] == '\\')
		{
			if ((*save_ptr)[*i + 1])
			{
				if ((*save_ptr)[*i + 1] == delim)
				{
					(*i) += 2;
					continue ;
				}
			}
		}
		if ((*save_ptr)[*i] == delim)
			break ;
		(*i)++;
	}
	if (!(*save_ptr)[*i])
	{
		data->error = true;
		data->last_exit_code = 2;
		ft_exit_error("Invalid format");
		return (0);
	}
	return (1);
}
