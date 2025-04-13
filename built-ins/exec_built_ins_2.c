/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loruzqui <loruzqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:52:58 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/13 21:53:38 by loruzqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	exec_env(t_parser *cmd, t_data *data, int *stdinout)
{
	ft_env(cmd->args, data->env);
	unset_std(stdinout);
	return (true);
}

bool	exec_unset(t_parser *cmd, t_data *data, int *stdinout)
{
	ft_unset(cmd->args, data->env);
	ft_free_split(data->env_arr);
	data->env_arr = ft_lsttoa(*data);
	unset_std(stdinout);
	return (true);
}

bool	exec_export(t_parser *cmd, t_data *data, int *stdinout)
{
	ft_export(cmd->args, data);
	ft_free_split(data->env_arr);
	data->env_arr = ft_lsttoa(*data);
	unset_std(stdinout);
	return (true);
}
