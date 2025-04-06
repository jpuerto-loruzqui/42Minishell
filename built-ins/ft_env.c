/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:03:06 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/05 19:03:08 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **args, char **envp)
{
	(void)args;
	while (*envp)
	{
		ft_putstr_fd(*envp, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		envp++;
	}
	return (1);
}
