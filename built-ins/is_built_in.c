/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 16:04:32 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/08 19:06:44 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_built_in(t_parser *commands, t_data *data)
{
    if (ft_strncmp(commands->args[0], "exit", 5) == 0)
        return (ft_exit(commands), true);
    else if (ft_strncmp(commands->args[0], "cd", 3) == 0)
        return (ft_cd(commands->args), true);
    else if (ft_strncmp(commands->args[0], "pwd", 4) == 0)
        return (ft_pwd(commands->args), true);
    else if (ft_strncmp(commands->args[0], "echo", 5) == 0)
        return (ft_echo(commands->args), true);
    else if (ft_strncmp(commands->args[0], "env", 4) == 0)
        return (ft_env(commands->args, data->env), true);
    else if (ft_strncmp(commands->args[0], "unset", 6) == 0)
    {
        ft_unset(commands->args, data->env);
        ft_free_split(data->env_arr);
        data->env_arr = ft_lsttoa(*data);
		return (true);
    }
	else if (ft_strncmp(commands->args[0], "export", 7) == 0)
	{
		ft_export(commands->args, data);
		ft_free_split(data->env_arr);
        data->env_arr = ft_lsttoa(*data);
        return ( true);
	}
    return false;
}
