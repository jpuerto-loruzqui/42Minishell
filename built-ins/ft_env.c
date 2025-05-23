/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:03:06 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/08 16:18:38 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **args, t_env *envp)
{
	char	*save_ptr;

	(void)args;
	if (args[1])
		return (1);
	while (envp)
	{
		save_ptr = ft_strchr(envp->content, '=');
		if (ft_strncmp(save_ptr, "=", 2) != 0)
		{
			ft_putstr_fd(envp->content, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		envp = envp->next;
	}
	return (0);
}
