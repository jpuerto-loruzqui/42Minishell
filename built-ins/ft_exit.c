/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:40:38 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/10 12:24:06 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_parser *parser)
{
	int		exit_code;
	int		exit_atoi;

	exit_code = EXIT_SUCCESS;
	exit_atoi = 0;
	if (parser->args[1])
		exit_atoi = ft_atoi(parser->args[1]);
	if (exit_atoi != 0)
		exit_code = exit_atoi;
	free_parser(parser);
	printf("Saliendo de la shell...\n");
	exit(exit_code);
}
