/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:40:38 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/21 16:02:35 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_parser *parser)
{
	int		exit_code;
	int		exit_atoi;
	int		i;

	exit_code = EXIT_SUCCESS;
	exit_atoi = 0;
	i = 0;
	if (parser->args[1])
	{
		while (parser->args[1][i])
		{
			if (!ft_isdigit(parser->args[1][i]))
			{
				ft_putstr_fd("exit: Numeric argument required: ", 2);
				ft_putendl_fd(parser->args[1], 2);
				exit(2);
			}
			i++;
		}
		exit_atoi = ft_atoi(parser->args[1]);
	}
	if (exit_atoi != 0)
		exit_code = exit_atoi;
	ft_free_parser(parser);
	exit(exit_code);
}
