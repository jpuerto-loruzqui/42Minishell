/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:04:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/03/26 16:05:35 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_built_in(t_parser *commands, char ***envp)
{
	if (ft_strncmp(commands->args[0], "exit", 4) == 0)
		return (ft_exit(commands), true);
	else if (ft_strncmp(commands->args[0], "cd", 2) == 0)
		return (ft_cd(commands->args), true);
	else if (ft_strncmp(commands->args[0], "pwd", 3) == 0)
		return (ft_pwd(commands->args), true);
	else if (ft_strncmp(commands->args[0], "echo", 4) == 0)
		return (ft_echo(commands->args), true);
	else if (ft_strncmp(commands->args[0], "env", 3) == 0)
		return (ft_env(commands->args, *envp), true);
	else if (ft_strncmp(commands->args[0], "unset", 5) == 0)
	{
		*envp = ft_unset(commands->args, envp);
		return (true);
	}
	return (false);
}
