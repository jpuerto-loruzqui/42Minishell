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

bool	is_built_in(t_parser *commands)
{
	if (ft_strncmp(commands->args[0], "exit", 4) == 0)
		return (ft_exit(), true);
	else if (ft_strncmp(commands->args[0], "cd", 2) == 0)
		return (ft_cd(commands->args), true);
	else if (ft_strncmp(commands->args[0], "pwd", 3) == 0)
		return (ft_pwd(commands->args), true);
	return (false);
}
