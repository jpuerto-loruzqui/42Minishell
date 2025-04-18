/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:21:06 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/17 19:40:31 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_exec_jp(t_parser *cmd, int *stdinout)
{
	stdinout = ft_redir_builtin(cmd);
	ft_show_visualizer(cmd->args[1]);
	ft_unset_std(stdinout);
	return (true);
}

bool	ft_exec_exit(t_parser *cmd, int *stdinout)
{
	stdinout = ft_redir_builtin(cmd);
	ft_exit(cmd);
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

bool	ft_exec_pwd(t_parser *cmd, int *stdinout)
{
	stdinout = ft_redir_builtin(cmd);
	ft_pwd(cmd->args);
	ft_unset_std(stdinout);
	return (true);
}

bool	ft_exec_echo(t_parser *cmd, int *stdinout)
{
	stdinout = ft_redir_builtin(cmd);
	ft_echo(cmd->args);
	ft_unset_std(stdinout);
	return (true);
}
