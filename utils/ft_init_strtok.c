/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_strtok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:04:14 by jpuerto           #+#    #+#             */
/*   Updated: 2025/04/18 12:04:33 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
