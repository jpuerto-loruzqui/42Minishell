/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:40:38 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/18 13:15:47 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_parser *parser, t_data *data)
{
	int		exit_code;
	int		exit_atoi;
	int i;

	i = 0;
	exit_code = EXIT_SUCCESS;
	exit_atoi = 0;
	if (parser->args[1])
	{
		while (parser->args[1][i])
		{
			if (!ft_isdigit(parser->args[1][i]))
			{
				data->last_exit_code = 2;
				return (ft_putstr_fd("Numeric argumen required: ", 2),
					ft_putendl_fd(parser->args[1], 2));
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
