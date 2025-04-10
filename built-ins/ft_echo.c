/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:54:41 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/10 18:16:07 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_all_n(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **arg)
{
	bool	newline;

	newline = true;
	if (arg[1] == NULL)
		return (ft_putchar_fd('\n', STDOUT_FILENO), 1);
	arg++;
	if (ft_strncmp(*arg, "-n", 2) == 0 && check_all_n(*arg))
	{
		newline = false;
		arg++;
	}
	while (*arg)
	{
		ft_putstr_fd(*arg, STDOUT_FILENO);
		ft_putchar_fd(' ', STDOUT_FILENO);
		arg++;
	}
	if (newline == true)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (1);
}
