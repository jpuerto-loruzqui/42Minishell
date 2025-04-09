/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:53:08 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/04/09 15:18:29 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unrecognized_error(char *command)
{
	char *str_cmd;

	str_cmd = command;
	while (*str_cmd)
	{
		if (!ft_isprint(*str_cmd))
		{
			ft_putstr_fd("Unrecognized command", 2);
			ft_putchar_fd('\n', 2);
			return ;
		}
		str_cmd++;
	}
	ft_putstr_fd("Unrecognized command: ", 2);
	ft_putstr_fd(command, 2);
	ft_putchar_fd('\n', 2);
}

void	exit_error(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	rl_on_new_line();
	rl_replace_line("", 0);
}
