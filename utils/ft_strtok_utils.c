/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:17:25 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/16 09:56:44 by loruzqui         ###   ########.fr       */
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
	s->token = "";
	s->separator = ft_check_separator(s->save_ptr);
}
