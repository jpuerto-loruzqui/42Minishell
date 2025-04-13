/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:40:38 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/13 14:16:03 by loruzqui         ###   ########.fr       */
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
	exit(exit_code);
}
