/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parserlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:07:56 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/27 17:07:58 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parserlen(t_parser *parser)
{
	int	len;

	len = 0;
	while (parser)
	{
		len++;
		parser = parser->next;
	}
	return (len);
}
