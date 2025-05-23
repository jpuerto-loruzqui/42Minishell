/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto- <jpuerto-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:21:06 by loruzqui          #+#    #+#             */
/*   Updated: 2025/05/08 16:44:19 by jpuerto-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_exec_jp(t_parser *cmd, int *stdinout, t_data *data)
{
	stdinout = ft_redir_builtin(cmd);
	ft_show_visualizer(cmd->args[1]);
	signal(SIGINT, ft_sigint_handler);
	ft_unset_std(stdinout);
	if (data->error == false)
		data->last_exit_code = 0;
	return (true);
}

bool	ft_exec_exit(t_parser *cmd, int *stdinout, t_data *data)
{
	stdinout = ft_redir_builtin(cmd);
	ft_exit(cmd, data);
	ft_unset_std(stdinout);
	return (true);
}

bool	ft_exec_cd(t_parser *cmd, t_data *data, int *stdinout)
{
	stdinout = ft_redir_builtin(cmd);
	ft_cd(cmd->args, data);
	ft_unset_std(stdinout);
	return (true);
}

bool	ft_exec_pwd(t_parser *cmd, int *stdinout, t_data *data)
{
	stdinout = ft_redir_builtin(cmd);
	if (ft_pwd(cmd->args) == 1)
	{
		data->error = true;
		data->last_exit_code = 1;
	}
	ft_unset_std(stdinout);
	if (data->error == false)
		data->last_exit_code = 0;
	return (true);
}

bool	ft_exec_echo(t_parser *cmd, int *stdinout)
{
	stdinout = ft_redir_builtin(cmd);
	ft_echo(cmd->args);
	ft_unset_std(stdinout);
	return (true);
}
