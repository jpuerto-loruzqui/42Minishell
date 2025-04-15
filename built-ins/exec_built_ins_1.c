/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_ins_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpuerto <jpuerto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:21:06 by loruzqui          #+#    #+#             */
/*   Updated: 2025/04/14 20:28:34 by jpuerto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	exec_jp(t_parser *cmd, int *stdinout)
{
	stdinout = redir_builtin(cmd);
	show_visualizer(cmd->args[1]);
	unset_std(stdinout);
	return (true);
}

bool	exec_exit(t_parser *cmd, int *stdinout)
{
	stdinout = redir_builtin(cmd);
	ft_exit(cmd);
	unset_std(stdinout);
	return (true);
}

bool	exec_cd(t_parser *cmd, t_data *data, int *stdinout)
{
	stdinout = redir_builtin(cmd);
	ft_cd(cmd->args, data);
	unset_std(stdinout);
	return (true);
}

bool	exec_pwd(t_parser *cmd, int *stdinout)
{
	stdinout = redir_builtin(cmd);
	ft_pwd(cmd->args);
	unset_std(stdinout);
	return (true);
}

bool	exec_echo(t_parser *cmd, int *stdinout)
{
	stdinout = redir_builtin(cmd);
	ft_echo(cmd->args);
	unset_std(stdinout);
	return (true);
}
