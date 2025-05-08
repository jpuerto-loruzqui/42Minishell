/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:53:08 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/05/08 16:34:36 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_valid_char(char command)
{
	static int	flag;

	if (flag == 0 && command == '\\' && !command + 1)
		flag = 0;
	if (command == '\\' && flag == 1)
	{
		flag = 0;
		return (1);
	}
	if (command == '\\')
	{
		flag = 1;
		return (0);
	}
	flag = 0;
	return (1);
}

void	ft_exit_error(char *message, t_data *data, int code)
{
	if (data)
		data->error = true;
	if (data && code != 0)
		data->last_exit_code = 1;
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	rl_on_new_line();
	rl_replace_line("", 0);
}
