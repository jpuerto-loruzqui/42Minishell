/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:40:38 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/21 15:40:40 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_parser *parser)
{
	free_parser(parser);
	printf("Saliendo de la shell...\n");
	exit(EXIT_SUCCESS);
}
