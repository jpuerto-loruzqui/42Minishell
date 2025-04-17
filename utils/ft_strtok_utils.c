/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:17:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/16 18:32:29 by jpuerto          ###   ########.fr       */
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

void	init_strtok_struct(t_strtok *s, char *str)
{
	if (str)
		s->save_ptr = str;
	s->separator = check_separator(s->save_ptr);
	if (s->token)
	{
		free(s->token);
		s->token = NULL;
	}
	s->token = ft_strdup("");
}

