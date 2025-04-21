/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:52:58 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/18 13:19:47 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_exec_env(t_parser *cmd, t_data *data, int *stdinout)
{
	ft_env(cmd->args, data->env);
	ft_unset_std(stdinout);
	return (true);
}

bool	ft_exec_unset(t_parser *cmd, t_data *data, int *stdinout)
{
	ft_unset(cmd->args, data->env);
	ft_free_split(data->env_arr);
	data->env_arr = ft_lsttoa(*data);
	ft_unset_std(stdinout);
	return (true);
}

bool	ft_exec_export(t_parser *cmd, t_data *data, int *stdinout)
{
	ft_export(cmd->args, data);
	ft_free_split(data->env_arr);
	data->env_arr = ft_lsttoa(*data);
	ft_unset_std(stdinout);
	if (data->error == false)
		data->last_exit_code = 0;
	return (true);
}
