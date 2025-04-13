/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:53:08 by jpuerto-          #+#    #+#             */
/*   Updated: 2025/04/13 15:59:29 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_char(char command)
{
	static int	flag;

	if (ft_strchr(INVALID_CHARS, command))
		return (0);
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

int	is_valid_slash(char command)
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

void	exit_error(char *message)
{
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	rl_on_new_line();
	rl_replace_line("", 0);
}
