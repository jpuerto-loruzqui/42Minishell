/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:54:41 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/05 18:54:43 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **arg) // no saca al > outfile
{
	bool	newline;

	newline = true;
	arg++;
	if (ft_strncmp(*arg, "-n", 2) == 0)
	{
		newline = false;
		arg++;
	}
	while (*arg)
	{
		ft_putstr_fd(*arg, STDOUT_FILENO);
		ft_putchar_fd(' ', STDERR_FILENO);
		arg++;
	}
	if (newline == true)
		ft_putchar_fd('\n', STDERR_FILENO);
	return (1);
}
