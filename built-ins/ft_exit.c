/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:40:38 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/08 11:21:51 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_is_numeric_argument(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && arg[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_parser *parser, t_data *data)
{
	int	exit_code;
	int	exit_atoi;

	exit_code = EXIT_SUCCESS;
	exit_atoi = 0;
	if (parser->args[1] && parser->args[2])
		return (ft_exit_error("Error: too many arguments", data, 1));
	if (parser->args[1])
	{
		if (!ft_is_numeric_argument(parser->args[1]))
		{
			data->last_exit_code = 2;
			return (ft_putstr_fd("Numeric argument required: ", 2),
				ft_putendl_fd(parser->args[1], 2));
		}
		exit_atoi = ft_atoi(parser->args[1]);
	}
	if (exit_atoi != 0)
		exit_code = exit_atoi;
	ft_free_parser(parser);
	exit(exit_code);
}
